#include "BaseController.hpp"
#include "TriggerController.hpp"
#include "System.hpp"
#include "Ultrasonic.hpp"
#include "Microphone.hpp"
#include "SerialTalk.hpp"


namespace Machine{
    enum Mode{
        Sonar,
        Sound,
        Service
    };
    const int pinButton = 11;
    extern Mode mode;

    void init();
    int targetLock();
    void test();
    int getButtonPressed();
}
