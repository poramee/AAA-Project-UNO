#include "BaseController.hpp"
#include "TriggerController.hpp"
#include "System.hpp"
#include "Ultrasonic.hpp"

namespace Machine{
    enum Mode{
        Sonar,
        Sound
    };
    extern Mode mode;

    void init();
    bool targetLock();
    void test();
}
