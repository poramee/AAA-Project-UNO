#include <SoftwareSerial.h>
#include <Arduino.h>

namespace SerialTalk{
    const int pinTx = A1;
    const int pinRx = A2;

    extern SoftwareSerial softSerial;

    enum class TopRow{
        null = '\0',
        Sonar = 'M',
        Sound = 'D',
        Reload = 'R'
    };
    enum class BottomRow{
        null = '\0',
        Idle = 'i',
        Watch = 'w',
        TargetLocking = 'l',
        Fire = 'f',
        ReloadNotify = 'r',
        Blank = 'n'
    };

    void init();
    void LCD(TopRow top,BottomRow bottom);

}