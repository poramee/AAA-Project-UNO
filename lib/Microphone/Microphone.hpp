#include <Arduino.h>

namespace Microphone{
    const int pin = A0;
    extern int lastSound;
    bool detect();
}