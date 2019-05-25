#include "AAAMachine.hpp"
#include <Arduino.h>

void setup() {
  Machine::init();
  System::machineState = System::Status::Watch;
  Machine::mode = Machine::Mode::Service;
  Base::angle = 45;
}

void sonar();
void sound();
void reload();

int cnt = 0;

int lastSounds = analogRead(Microphone::pin);

void loop() {
  if (Machine::mode == Machine::Mode::Sonar) sonar();
  else if (Machine::mode == Machine::Mode::Sound) sound();
  else if(Machine::mode == Machine::Mode::Reload) reload();
  else if (Machine::mode == Machine::Mode::Service) {
    sound();
    // int read = analogRead(Microphone::pin);
    // if(read - lastSounds > 600) Serial.println(read - lastSounds);
    // else lastSounds = read;
  }
}

int lockOutOfRange = 0;

void sonar() {
  using namespace System;
  using namespace SerialTalk;

  const int buttonPressed = Machine::getButtonPressed();

  if(buttonPressed == 1){
    if(machineState != Status::Idle) machineState = Status::Idle;
    else machineState = Status::Watch;
  }
  else if(buttonPressed == 2){
    Machine::mode = Machine::Mode::Sound;
    return;
  }
  if(machineState == Status::Idle) LCD(TopRow::Sonar, BottomRow::Idle);
  else if (machineState == Status::Watch) {
    Base::watch(0);
    LCD(TopRow::Sonar, BottomRow::Watch);
    Serial.println("WATCHING...");
    double avgLeft = 0;
    double avgCenter = 0;
    double avgRight = 0;
    for(int i = 0;i < 5;++i){
      avgLeft += Ultrasonic::left.ping();
      delay(5);
      avgCenter += Ultrasonic::center.ping();
      delay(5);
      avgRight += Ultrasonic::right.ping();
      delay(5);
    }
    avgLeft /= 5;
    avgCenter /= 5;
    avgRight /= 5;
    if (avgLeft < Ultrasonic::DEFAULT_TRESHOLD or avgCenter < Ultrasonic::DEFAULT_TRESHOLD or avgRight < Ultrasonic::DEFAULT_TRESHOLD) {
      Serial.println("DETECTED");
      machineState = Status::TargetLocking;
    }
    delay(50);
  } else if (machineState == Status::TargetLocking) {
    LCD(TopRow::Sonar, BottomRow::TargetLocking);
    Serial.print("LOCKING...");
    const int returnValue = Machine::targetLock();
    Serial.println(returnValue);
    if (returnValue == 1)
      machineState = Status::Fire;
    else if (returnValue == -1)
      machineState = Status::Watch;
  } else if (machineState == Status::Fire) {
    LCD(TopRow::Sonar, BottomRow::Fire);
    Serial.println("FIRE");
    Trigger::rotateCW(false);
    if (Machine::targetLock() == -1) {
      ++lockOutOfRange;
    } else {
      lockOutOfRange = 0;
    }
    if (lockOutOfRange >= 10){
      machineState = Status::Watch;
      Trigger::stop();
    }
  }
}

void sound() {
  using namespace System;
  using namespace Machine;

  const int buttonPressed = Machine::getButtonPressed();

  if(buttonPressed == 1){
    if(machineState != Status::Idle) machineState = Status::Idle;
    else if(machineState == Status::Idle) machineState = Status::Watch;
  }
  else if(buttonPressed == 2){
    Machine::mode = Machine::Mode::Reload;
  }
  if (machineState == Status::Watch) {
    Base::watch(200);
    LCD(SerialTalk::TopRow::Sound,SerialTalk::BottomRow::Watch);
    if (Microphone::detect())
      machineState = Status::Fire;
  } else if (machineState == Status::Fire) {
    LCD(SerialTalk::TopRow::Sound, SerialTalk::BottomRow::Fire);
    Trigger::rotateCW(false);
    delay(500);
    Trigger::stop();
    machineState = Status::Watch;
  }
}

int lastPress = LOW;
void reload() {
  using namespace SerialTalk;
  LCD(TopRow::Reload, BottomRow::Blank);
  const int read = digitalRead(Machine::pinButton);
  const int buttonPressed = Machine::getButtonPressed();
  if (buttonPressed == 2){
    Machine::mode = Machine::Mode::Sonar;
  }
  else {
    if (read == HIGH and lastPress == LOW) {
      Trigger::rotateCCW(false);
      lastPress = HIGH;
    } else if (read == LOW and lastPress == HIGH) {
      Trigger::stop();
      lastPress = LOW;
    }
    if (Trigger::rotation < 0)
      Trigger::rotation = 0;
  }
}