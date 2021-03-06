#include "AAAMachine.hpp"
#include <Arduino.h>

void setup() {
  Machine::init();
  System::machineState = System::Status::Idle;
  Machine::mode = Machine::Mode::Sonar;
  Base::servo.write(Base::angle);
  delay(300);
  SerialTalk::LCD(SerialTalk::TopRow::Sonar, SerialTalk::BottomRow::Idle);
}

void sonar();
void sound();
void reload();

int cnt = 0;

int lastSounds = analogRead(Microphone::pin);

void loop() {
  if (Machine::mode == Machine::Mode::Sonar)
    sonar();
  else if (Machine::mode == Machine::Mode::Sound)
    sound();
  else if (Machine::mode == Machine::Mode::Reload)
    reload();
  else if (Machine::mode == Machine::Mode::Service) {
    // Base::watch(250);
    // System::machineState = System::Status::Watch;
    // sound();
    // LCD(SerialTalk::TopRow::Sound,SerialTalk::BottomRow::null);
    // delay(1000);
    // LCD(SerialTalk::TopRow::Reload, SerialTalk::BottomRow::null);
    // delay(1000);
    Serial.print(Ultrasonic::left.ping());
    Serial.print("\t");
    Serial.print(Ultrasonic::center.ping());
    Serial.print("\t");
    Serial.println(Ultrasonic::right.ping());

    // Trigger::rotateCW();
    // Serial.println(digitalRead(12));
    // Serial.println(digitalRead(12));
    // Microphone::detect();
    // Serial.println(read);
    // sonar();
    //  Base::watch();
    // Serial.println(digitalRead(12));
    delay(50);
  }
}

int lockOutOfRange = 0;

void sonar() {
  using namespace System;
  using namespace SerialTalk;

  const int buttonPressed = Machine::getButtonPressed();
  Serial.println(buttonPressed);
  if (buttonPressed == 1) {
    if (machineState != Status::Idle)
      machineState = Status::Idle;
    else{
      machineState = Status::Watch;
      // LCD(TopRow::Sonar, BottomRow::Watch);
    }
  } else if (buttonPressed == 2) {
    Machine::mode = Machine::Mode::Sound;
    System::machineState = System::Status::Idle;
    return;
  }
  if (machineState == Status::Idle) {
    Trigger::stop();
    LCD(TopRow::Sonar, BottomRow::Idle);

  } else if (machineState == Status::Watch) {
    Base::watch(0);
    LCD(TopRow::Sonar, BottomRow::Watch);
    Serial.println("WATCHING...");
    double avgLeft = 0;
    double avgCenter = 0;
    double avgRight = 0;
    for (int i = 0; i < 10; ++i) {
      avgLeft += Ultrasonic::left.ping();
      avgCenter += Ultrasonic::center.ping();
      avgRight += Ultrasonic::right.ping();
      delay(5);
    }
    avgLeft /= 10;
    avgCenter /= 10;
    avgRight /= 10;
    if ((avgLeft < Ultrasonic::DEFAULT_TRESHOLD and avgLeft > 0) or
        (avgCenter < Ultrasonic::DEFAULT_TRESHOLD and avgCenter > 0) or
        (avgRight < Ultrasonic::DEFAULT_TRESHOLD and avgRight > 0)) {
      Serial.print("DETECTED\t");
      Serial.print(avgLeft);
      Serial.print("\t");
      Serial.print(avgCenter);
      Serial.print("\t");
      Serial.println(avgRight);
      machineState = Status::TargetLocking;
    }
    delay(50);
  } else if (machineState == Status::TargetLocking) {
    // LCD(TopRow::Sonar, BottomRow::TargetLocking);
    Serial.print("LOCKING...");
    const int returnValue = Machine::targetLock();
    Serial.println(returnValue);
    if (returnValue == 1)
      machineState = Status::Fire;
    if (Machine::targetLock() == -1) {
      ++lockOutOfRange;
    } else {
      lockOutOfRange = 0;
    }
    if (lockOutOfRange >= 5) {
      machineState = Status::Watch;
      lockOutOfRange = 0;
    }
  } else if (machineState == Status::Fire) {
    if (Trigger::outOfRange()) {
      machineState = Status::Reload;
      return;
    } else {
      LCD(TopRow::Sonar, BottomRow::Fire);
      Serial.println("FIRE");
      Trigger::rotateCW();
      if (Machine::targetLock() == -1) {
        ++lockOutOfRange;
      } else {
        lockOutOfRange = 0;
      }
      if (lockOutOfRange >= 10) {
        machineState = Status::Watch;
        lockOutOfRange = 0;
        Trigger::stop();
      }
    }
  } else if (machineState == Status::Reload) {
    Trigger::stop();
    LCD(TopRow::Sonar, BottomRow::ReloadNotify);
    Base::servo.write(Base::angle);
  }
}

void sound() {
  using namespace System;
  using namespace Machine;
  using namespace SerialTalk;

  const int buttonPressed = Machine::getButtonPressed();

  if (buttonPressed == 1) {
    if (machineState != Status::Idle) {
      machineState = Status::Idle;
    } else if (machineState == Status::Idle)
      machineState = Status::Watch;
  } else if (buttonPressed == 2) {
    Machine::mode = Machine::Mode::Reload;
    System::machineState = System::Status::Idle;
    return;
  }

  if (machineState == Status::Idle) {
    LCD(SerialTalk::TopRow::Sound, SerialTalk::BottomRow::Idle);
  } else if (machineState == Status::Watch) {
    LCD(SerialTalk::TopRow::Sound, SerialTalk::BottomRow::Watch);
    Base::watch(250);
    if (Microphone::detect()) {
      machineState = Status::Fire;
      Serial.println("Detected");
    }
  } else if (machineState == Status::Fire) {
    if (Trigger::outOfRange()) {
      machineState = Status::Reload;
      return;
    } else {
      LCD(SerialTalk::TopRow::Sound, SerialTalk::BottomRow::Fire);
      Trigger::rotateCW(false);
      delay(500);
      Trigger::stop();
      machineState = Status::Watch;
    }
  } else if (machineState == Status::Reload) {
    Trigger::stop();
    LCD(TopRow::Sound, BottomRow::ReloadNotify);
    Base::servo.write(Base::angle);
  }
}

int lastPress = LOW;
void reload() {
  using namespace SerialTalk;
  LCD(TopRow::Reload, BottomRow::Blank);
  const int read = digitalRead(Machine::pinButton);
  const int buttonPressed = Machine::getButtonPressed();
  if (buttonPressed == 2) {
    Machine::mode = Machine::Mode::Sonar;
    System::machineState = System::Status::Idle;
    if (Trigger::rotation < 0) Trigger::rotation = 0;
    return;
  } else if (buttonPressed == 0) {
    if (read == HIGH and lastPress == LOW) {
      Trigger::rotateCCW(false);
      Serial.println("rotate");
      lastPress = HIGH;
    } else if (read == LOW and lastPress == HIGH) {
      Trigger::stop();
      lastPress = LOW;
    }
    if (Trigger::rotation < 0)
      Trigger::rotation = 0;
  }
}