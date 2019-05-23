#include "Ultrasonic.hpp"

using namespace Ultrasonic;

Sonar Ultrasonic::left(pinLeftTrig,pinLeftEcho,MAX_DISTANCE);
Sonar Ultrasonic::center(pinCenterTrig,pinCenterEcho,MAX_DISTANCE);
Sonar Ultrasonic::right(pinRightTrig,pinRightEcho,MAX_DISTANCE);