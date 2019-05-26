#include "Microphone.hpp"

using namespace Microphone;

int Microphone::lastSound = analogRead(Microphone::pin);

bool Microphone::detect(){
    const int read = analogRead(Microphone::pin);
    if(read - lastSound > 350 and read > 750) Serial.println(read);
    else lastSound = read;
    return read - lastSound > 350;
}