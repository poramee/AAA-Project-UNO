#include "AAAMachine.hpp"

using namespace Machine;

Mode Machine::mode = Mode::Sonar;

void Machine::init() {
  Base::init();
  Trigger::init();
  SerialTalk::init();
  pinMode(pinButton,INPUT);
  Serial.begin(9600);
}

unsigned long long targetMillis = millis();
int lastLeftPing;
int lastCenterPing;
int lastRightPing;


int Machine::targetLock(){
  using namespace Ultrasonic;
  using namespace Base;

  int leftPing;
  int centerPing;
  int rightPing;

  if (millis() - targetMillis > 50) {
    leftPing = left.ping();
    centerPing = center.ping();
    rightPing = right.ping();

    Serial.print(leftPing);
    Serial.print("\t");
    Serial.print(centerPing);
    Serial.print("\t");
    Serial.print(rightPing);
    Serial.print("    ");
  } else{
    leftPing = lastLeftPing;
    centerPing = lastCenterPing;
    rightPing = lastRightPing;
  }

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
int buttonLastPress = LOW;
unsigned long long buttonLastPressMillis = 0;
int Machine::getButtonPressed(){
  const int read = digitalRead(pinButton);
  if(read == HIGH and buttonLastPress == LOW){
    buttonLastPress = HIGH;
    ++press;
    buttonLastPressMillis = millis();
  }
  else if(read == HIGH and buttonLastPress == HIGH and millis() - buttonLastPressMillis >= 300){
    press = 0;
    return 0;
  } 
  else if(read == LOW and buttonLastPress == HIGH) buttonLastPress = LOW;
  else if(read == LOW and buttonLastPress == LOW and millis() - buttonLastPressMillis >= 300){
    const int ret = press;
    press = 0;
    return ret;
  }
  return 0;
}