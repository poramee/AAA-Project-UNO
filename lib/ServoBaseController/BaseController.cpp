#include "BaseController.hpp"
#include <Arduino.h>

using namespace Base;

Servo Base::servo;
int Base::angle = 0;

void Base::init() { servo.attach(pin); }
void Base::angleIncrement() {
  if (++angle > 180) angle = 180;
  servo.write(angle);
}
void Base::angleDecrement() {
  if (--angle < 0)
    angle = 0;
  servo.write(angle);
}
bool Base::isBounded() { return angle == 180 || angle == 0; }

bool watchMode = 0;
void Base::watch(unsigned long delayTime) {
  if (watchMode == 0)
    angleIncrement();
  else
    angleDecrement();
  if (isBounded())
    watchMode = !watchMode;
  delay(delayTime);
}
void Base::watch() { watch(50); }