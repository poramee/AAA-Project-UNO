#include "TriggerController.hpp"

using namespace Trigger;

Trigger::Status lastState = Trigger::Status::Stop;
unsigned long long Trigger::lastStateMillis = 0;
long long Trigger::rotation = 0;

void Trigger::init() {
  pinMode(pinForward,OUTPUT);
  pinMode(pinBackward,OUTPUT);
  Trigger::stop();
  lastState =  Trigger::Status::Stop;
  lastStateMillis = millis();
}
void Trigger::rotateCW(bool outOfRangeCheck) {
  if (outOfRangeCheck and outOfRange()) {
    Serial.println("OUT OF RANGE, RELOAD");
    stop();
    return;
  }
  if(lastState == Status::RotateCCW){
    rotation -= (millis() - lastStateMillis);
    digitalWrite(pinForward, HIGH);
    digitalWrite(pinBackward, LOW);
  }
  else if(lastState == Status::RotateCW){
    rotation += (millis() - lastStateMillis);
  }
  else{
    digitalWrite(pinForward, HIGH);
    digitalWrite(pinBackward, LOW);
  }
  lastStateMillis = millis();
  lastState = Status::RotateCW;
}
void Trigger::rotateCW(){
  rotateCW(true);
}
void Trigger::rotateCCW(bool outOfRangeCheck){
  if(outOfRangeCheck and outOfRange()){
    stop();
    return;
  }
  if(lastState == Status::RotateCCW){
    rotation -= (millis() - lastStateMillis);
  }
  else if(lastState == Status::RotateCW){
    rotation += (millis() - lastStateMillis);
  }
  lastStateMillis = millis();
  lastState = Status::RotateCCW;
  digitalWrite(pinForward, LOW);
  digitalWrite(pinBackward, HIGH);
}
void Trigger::rotateCCW() {
  rotateCCW(true);
}
void Trigger::stop() {
  if(lastState == Status::RotateCCW){
    rotation -= (millis() - lastStateMillis);
  }
  else if(lastState == Status::RotateCW){
    rotation += (millis() - lastStateMillis);
  }
  lastStateMillis = millis();
  lastState = Status::Stop;
  digitalWrite(pinForward, LOW);
  digitalWrite(pinBackward, LOW);
}
void Trigger::test() {
  rotateCW();
  delay(2000);
  rotateCCW();
}
bool Trigger::outOfRange(){
  return (rotation < 0 || rotation > 10000);
}