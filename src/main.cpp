#include "AAAMachine.hpp"
#include <Arduino.h>

void setup() {
  Machine::init();
  System::machineState = System::Status::Watch;
  Machine::mode = Machine::Mode::Service;
  pinMode(11, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void sonar();
void sound();

int cnt = 0;

void loop() {
  if (Machine::mode == Machine::Mode::Sonar)
    sonar();
  else if (Machine::mode == Machine::Mode::Sound)
    sound();
  else if (Machine::mode == Machine::Mode::Service) {
    // if(Microphone::detect()){
    //   Serial.print(cnt++);
    //   Serial.println("FIRE!!");
    // }
    // const int read = analogRead(Microphone::pin);
    if(Microphone::detect()){
      Serial.print(++cnt);
      Serial.println("  detect");
    }
  }
}

int lockOutOfRange = 0;

void sonar() {
  using namespace System;
  if (machineState == Status::Idle) {
  }
  if (machineState == Status::Watch) {
    Base::watch();
    Serial.println("WATCHING...");
    if (Ultrasonic::left.detect() or Ultrasonic::center.detect() or
        Ultrasonic::right.detect()) {
      Serial.println("DETECTED");
      machineState = Status::TargetLocking;
    }
  } else if (machineState == Status::TargetLocking) {
    Serial.print("LOCKING...");
    const int returnValue = Machine::targetLock();
    Serial.println(returnValue);
    if (returnValue == 1)
      machineState = Status::Fire;
    else if (returnValue == -1)
      machineState = Status::Watch;
  } else if (machineState == Status::Fire) {
    Serial.println("FIRE");
    if (Machine::targetLock() == -1) {
      ++lockOutOfRange;
    } else {
      lockOutOfRange = 0;
    }
    if (lockOutOfRange >= 20)
      machineState = Status::Watch;
  }
}

void sound() {
  using namespace System;
  using namespace Machine;

  if (machineState == Status::Watch) {
    Base::watch();
    if (Microphone::detect())
      machineState = Status::Fire;
  } else if (machineState == Status::Fire) {
    Trigger::rotateCW();
    delay(500);
    Trigger::stop();
    machineState = Status::Watch;
  }
}