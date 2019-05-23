#include <SoftwareSerial.h>

namespace Serial{
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