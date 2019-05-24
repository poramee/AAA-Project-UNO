#include "Microphone.hpp"

using namespace Microphone;

bool Microphone::detect(){
    double avg = 0;
    const int SAMPLE = 10;
    for(int i = 0;i < SAMPLE;++i){
        avg += analogRead(pin);
        delay(5);
    }
    avg /= SAMPLE;
    return avg > 200;
}