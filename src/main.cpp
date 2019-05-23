#include <Arduino.h>
#include "AAAMachine.hpp"

void setup() {
  Machine::init();
  System::machineState = System::Status::Idle;
  Machine::mode = Machine::Mode::Service;
  pinMode(11,INPUT_PULLUP);
  pinMode(13,OUTPUT);
}

void sonar();
void sound();

void loop() {
  if(Machine::mode == Machine::Mode::Sonar) sonar();
  else if(Machine::mode == Machine::Mode::Sound) sound();
  else if(Machine::mode == Machine::Mode::Service){
    // const int read = analogRead(Microphone::pin);
    // if(read > 200) digitalWrite(13,HIGH);
    // else digitalWrite(13,LOW);
    // sonar();
    Serial.print(Ultrasonic::left.ping());
    Serial.print(" ");
    Serial.print(Ultrasonic::center.ping());
    Serial.print(" ");
    Serial.println(Ultrasonic::right.ping());
    delay(50);
  }
}

void sonar(){
  if(System::machineState == System::Status::Idle){

  }
  if(System::machineState == System::Status::Watch){
    Base::watch();
    if(Ultrasonic::left.detect() or Ultrasonic::center.detect() or Ultrasonic::right.detect()){
      System::machineState = System::Status::TargetLocking;
    }
  }
  else if(System::machineState == System::Status::TargetLocking){
    const int returnValue = Machine::targetLock();
    if(returnValue == 1) System::machineState = System::Status::Fire;
    else if(returnValue == -1) System::machineState = System::Status::Watch;
  }
  else if(System::machineState == System::Status::Fire){
    System::machineState = System::Status::Watch;
  }
}

void sound(){
  using namespace System;
  using namespace Machine;

  if(machineState == Status::Watch){
    Base::watch();
    if(Microphone::detect()) machineState = Status::Fire;
  }
  else if(machineState == Status::Fire){
    Trigger::rotateCW();
    delay(500);
    Trigger::stop();
    machineState = Status::Watch;
  }
}