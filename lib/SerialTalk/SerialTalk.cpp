#include "SerialTalk.hpp"

using namespace Serial;

SoftwareSerial Serial::softSerial(Serial::pinRx,Serial::pinTx);

void Serial::sendTo(Command cmd,String str){
    String msg = "";
    if(cmd == Command::Speaker) msg += "SP";
    else if(cmd == Command::LCD) msg += "LC";
    else if(cmd == Command::BlinkLED) msg += "BL";
    msg += str;
    softSerial.println(msg); 
}