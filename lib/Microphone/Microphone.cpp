#include "Microphone.hpp"

using namespace Microphone;

bool Microphone::detect(){
    double avg = 0;
    const int SAMPLE = 1;
    for(int i = 0;i < SAMPLE;++i){
        avg += analogRead(pin);
        delay(1);
    }
    avg /= (double) SAMPLE;
    // Serial.println(avg);
    return avg > 200;
}