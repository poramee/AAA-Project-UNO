#include <Arduino.h>

namespace Trigger{
    const int pinForward = 10;
    const int pinBackward = 11;

    extern unsigned long long lastStateMillis;
    extern long long rotation;

    enum class Status{
        RotateCW,
        RotateCCW,
        Stop
    };

    void init();
    void rotateCW();
    void rotateCCW();
    void rotateCCW(bool outOfRangeCheck);
    void stop();
    void test();
    bool outOfRange();
}