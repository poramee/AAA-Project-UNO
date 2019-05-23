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
    const int read = analogRead(Microphone::pin);
    if(read > 200) digitalWrite(13,HIGH);
    else digitalWrite(13,LOW);
  }
}

void sonar(){
  if(System::machineState == System::Status::Idle){

  }
  if(System::machineState == System::Status::Watch){
    Base::servo.write(0);
    // if(Ultrasonic::left.detect() or Ultrasonic::center.detect() or Ultrasonic::right.detect()){
    //   System::machineState = System::Status::TargetLocking;
    // }
  }
  else if(System::machineState == System::Status::TargetLocking){
    if(Machine::targetLock()) System::machineState = System::Status::Fire;
  }
  else if(System::machineState == System::Status::Fire){

  }
}

void sound(){

}