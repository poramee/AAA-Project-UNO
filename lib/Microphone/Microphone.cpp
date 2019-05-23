#include "Microphone.hpp"

using namespace Microphone;

bool Microphone::detect(){
    return analogRead(pin) > 200;
}