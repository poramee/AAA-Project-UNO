#include "SerialTalk.hpp"

using namespace SerialTalk;

SoftwareSerial SerialTalk::softSerial(SerialTalk::pinRx,SerialTalk::pinTx);

void SerialTalk::init(){
    softSerial.begin(9600);
}

TopRow lastTop = TopRow::null;
BottomRow lastBottom = BottomRow::null;
void SerialTalk::LCD(TopRow top,BottomRow bottom){
    if(lastTop != top){
        lastTop = top;
        String pp = "";
        pp += (char)top;
        softSerial.print(pp);
        Serial.println(pp);
    }
    if(lastBottom != bottom){
        lastBottom = bottom;
        String pp = "";
        pp += (char)bottom;
        softSerial.print(pp);
    }
}