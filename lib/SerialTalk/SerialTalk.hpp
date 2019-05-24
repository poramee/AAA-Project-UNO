#include <SoftwareSerial.h>
#include <Arduino.h>

namespace SerialTalk{
    const int pinTx = A1;
    const int pinRx = A2;

    extern SoftwareSerial softSerial;

    enum Command{
        Speaker,
        LCD,
        BlinkLED
    };
    
    void sendTo(Command cmd,String string);
}