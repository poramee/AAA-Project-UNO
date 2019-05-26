#include "BaseController.hpp"
#include <Arduino.h>

using namespace Base;

Servo Base::servo;
int Base::angle = 30;

void Base::init() {
  servo.attach(pin);
  servo.write(angle);
}
void Base::angleIncrement() {
  angle += 5;
  if (angle > 150) angle = 150;
  servo.write(angle);
}
void Base::angleDecrement() {
  angle -= 5;
  if (angle < 30)
    angle = 30;
  servo.write(angle);
}
bool Base::isBounded() { return angle == 150 || angle == 30; }

bool watchMode = 0;
unsigned long long timer = 0;
void Base::watch(unsigned long delayTime) {
  if(millis() - timer < delayTime and timer != 0) return;
  else{
    timer = millis();
    Serial.print(angle);
    Serial.print("  ");
    Serial.println("turn!!!");
  }
  if (watchMode == 0)
    angleIncrement();
  else
    angleDecrement();
  if (isBounded())
    watchMode = !watchMode;
}
void Base::watch() { watch(50); }