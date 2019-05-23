#include "AAAMachine.hpp"

using namespace Machine;

Mode Machine::mode = Mode::Sonar;

void Machine::init() {
  Base::init();
  Trigger::init();
  Serial.begin(9600);
}

bool Machine::targetLock(){
  using namespace Ultrasonic;
  using namespace Base;

  int sonarDetect[3];
  sonarDetect[0] = left.detect();
  delay(20);
  sonarDetect[1] = center.detect();
  delay(20);
  sonarDetect[2] = right.detect();
  delay(20);

  Serial.print(sonarDetect[0]);
  Serial.print(sonarDetect[1]);
  Serial.println(sonarDetect[2]);
  if((sonarDetect[0] == 0 and sonarDetect[1] == 0 and sonarDetect[2] == 1) or (sonarDetect[0] == 0 and sonarDetect[1] == 1 and sonarDetect[2] == 1)) angleIncrement();
  else if((sonarDetect[0] == 1 and sonarDetect[1] == 0 and sonarDetect[2] == 0) or (sonarDetect[0] == 1 and sonarDetect[1] == 1 and sonarDetect[2] == 0)) angleDecrement();
  else return true;
  return false;
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