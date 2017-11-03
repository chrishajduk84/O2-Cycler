#include "Pump.h"
#include <stdlib.h>

//NOTE: See Heater.cpp for ISR routine

//These are static!!!
unsigned int Pump::pinList[NUM_CARTRIDGES*2];
unsigned int Pump::listLength;
Pump* Pump::pumpList[NUM_CARTRIDGES*2];

Pump::Pump(unsigned int _togglePin){
    //Assign the heating pin to the object
    for (int i = 0; i < listLength; i++){
        if (pinList[i] == _togglePin){
            //Serial.println("Initialized Heater Already Exists!");
            exit(1);
        }
    }
    //If the heating pin hasn't already been initialized, add it to the list
    pumpList[listLength] = this;
    pinMode(_togglePin, OUTPUT);
    pinList[listLength++] = togglePin = _togglePin; 
}

Pump::~Pump(){
    //Remove all entries in static variables
    bool removed = false;
    for (int i = 0; i < listLength; i++){
        if (pinList[i] == togglePin){
            removed = true;
        }
        if (removed){
            if (i+1 >= listLength) pinList[i] = 0;
            else pinList[i] = pinList[i+1];
        }
    }
}
   
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

void Pump::setPWM(int _duty){ //Hacks not really (hardware) PWM
  pwm = true;
  duty = _duty;
}

void Pump::stopPWM(){ //Hacks not really PWM
  pwm = false;
}
