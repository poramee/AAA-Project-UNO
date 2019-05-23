#include <Arduino.h>

namespace Trigger{
    const int pinForward = 10;
    const int pinBackward = 11;

    void init();
    void rotateCW();
    void rotateCCW();
    void stop();
    void test();
}