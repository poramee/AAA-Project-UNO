#include <NewPing.h>

namespace Ultrasonic{
    const int pinLeftTrig = 2;
    const int pinLeftEcho = 3;
    const int pinCenterTrig = 4;
    const int pinCenterEcho = 5;
    const int pinRightTrig = 6;
    const int pinRightEcho = 7;
    const int MAX_DISTANCE = 200;
    const int DEFAULT_TRESHOLD = 1500;

    class Sonar : public NewPing{
        public:
        Sonar(uint8_t trigger_pin, uint8_t echo_pin, unsigned int max_cm_distance):NewPing(trigger_pin,echo_pin,max_cm_distance){};
        ~Sonar(){}
        bool detect(unsigned int treshold){
            const unsigned int p = ping();
            return p < treshold && p > 0;
        }
        bool detect(){
            return detect(Ultrasonic::DEFAULT_TRESHOLD);
        }
    };

    extern Sonar left;
    extern Sonar center;
    extern Sonar right;

}