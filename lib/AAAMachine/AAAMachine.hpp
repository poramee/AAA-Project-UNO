#include "BaseController.hpp"
#include "TriggerController.hpp"
#include "System.hpp"
#include "Ultrasonic.hpp"
#include "Microphone.hpp"
#include "SerialTalk.hpp"


namespace Machine{
    enum class Mode{
        Sonar,
        Sound,
        Reload,
        Service
    };
    const int pinButton = 12;
    extern Mode mode;

    void init();
    int targetLock();
    void test();
    int getButtonPressed();
}
