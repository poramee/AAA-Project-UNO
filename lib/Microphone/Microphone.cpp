#include "Microphone.hpp"

using namespace Microphone;

bool Microphone::detect(){
    const int read = analogRead(pin);
    return read > 190;
}