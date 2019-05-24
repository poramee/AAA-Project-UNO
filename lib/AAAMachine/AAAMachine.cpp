#include "AAAMachine.hpp"

using namespace Machine;

Mode Machine::mode = Mode::Sonar;

void Machine::init() {
  Base::init();
  Trigger::init();
  Serial.begin(9600);
}

int Machine::targetLock(){
  using namespace Ultrasonic;
  using namespace Base;

  const int leftPing = left.ping();
  const int centerPing = center.ping();
  const int rightPing = right.ping();


  int min = 1e8;
  int minDirection = -1;
  if(leftPing < min and leftPing > 0){
    min = leftPing;
    minDirection = 0;
  }
  if(centerPing < min and centerPing > 0){
    min = centerPing;
    minDirection = 1;
  }
  if(rightPing < min and rightPing > 0){
    min = rightPing;
    minDirection = 2;
  }

  int returnValue = 0;
  if(min < DEFAULT_TRESHOLD){
    if(minDirection == 0){
      angleIncrement();
      returnValue = 0;
    }
    else if(minDirection == 2){
      angleDecrement();
      returnValue = 0;
    }
    else if(minDirection == 1) returnValue = 1;

  }
  else returnValue = -1;
  return returnValue;
}

void Machine::test(){
  Serial.print(Ultrasonic::left.ping());
  delay(20);
  Serial.print(" ");
  Serial.print(Ultrasonic::center.ping());
  delay(20);
  Serial.print(" ");
  Serial.println(Ultrasonic::right.ping());
  delay(20);
}

int press = 0;
int lastPress = LOW;
unsigned long long lastPressMillis = millis();
int Machine::getButtonPressed(){
  if(digitalRead(pinButton) == HIGH and lastPress == LOW){
    lastPress = HIGH;
    ++press;
    lastPressMillis = millis();
  }
  else if(digitalRead(pinButton) == LOW and lastPress == HIGH) lastPress = LOW;
  else if(digitalRead(pinButton) == LOW and lastPress == LOW and millis() - lastPressMillis >= 300){
    const int ret = press;
    press = 0;
    return ret;
  }
  return 0;
}