#include "TriggerController.hpp"

using namespace Trigger;

void Trigger::init() {
  pinMode(pinForward,OUTPUT);
  pinMode(pinBackward,OUTPUT);
}
void Trigger::rotateCW() {
  digitalWrite(pinForward, HIGH);
  digitalWrite(pinBackward, LOW);
}
void Trigger::rotateCCW() {
  digitalWrite(pinForward, LOW);
  digitalWrite(pinBackward, HIGH);
}
void Trigger::stop() {
  digitalWrite(pinForward, LOW);
  digitalWrite(pinBackward, LOW);
}
void Trigger::test() {
  rotateCW();
  delay(2000);
  rotateCCW();
}