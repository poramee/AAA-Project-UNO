#include "SerialTalk.hpp"

using namespace SerialTalk;

SoftwareSerial SerialTalk::softSerial(SerialTalk::pinRx,SerialTalk::pinTx);

void SerialTalk::sendTo(Command cmd,String str){
    String msg = "";
    if(cmd == Command::Speaker) msg += "SP";
    else if(cmd == Command::LCD) msg += "LC";
    else if(cmd == Command::BlinkLED) msg += "BL";
    msg += str;
    softSerial.println(msg); 
}