#include <Servo.h>

namespace Base {
const int pin = 9;

extern Servo servo;
extern int angle;

void init();
void angleIncrement();
void angleDecrement();
bool isBounded();
void watch(unsigned long delayTime);
void watch();
}