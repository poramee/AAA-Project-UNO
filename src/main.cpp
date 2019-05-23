#include <Arduino.h>
#include "AAAMachine.hpp"

void setup() {
  Machine::init();
  System::machineState = System::Status::Service;
}

void loop() {
  if(System::machineState == System::Status::TargetLocking){
    Machine::test();
  }
  else if(System::machineState == System::Status::Service){
    Base::watch();
  }
}