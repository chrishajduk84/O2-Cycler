#include "Pump.h"
#include <stdlib.h>

Pump::Pump(unsigned int _togglePin){
    //Assign the heating pin to the object
    if (_togglePin >= 0){
        pinMode(_togglePin, OUTPUT);
        togglePin = _togglePin;
    }else{
        //Serial.println("Invalid pinout!");
        exit(1);
    } 
}

Pump::~Pump(){}
   
void Pump::toggle(){
    digitalWrite(togglePin, !state);
    state = !state;
}

void Pump::toggle(bool _state){
    digitalWrite(togglePin, _state);
    state = _state;
}

bool Pump::getState(){
    return state;
}
