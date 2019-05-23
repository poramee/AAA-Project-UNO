#include "Microphone.hpp"

using namespace Microphone;

bool Microphone::detect(){
    return analogRead(A0) > 500;
}