#include "Valve.h"
#include <stdlib.h>

Valve::Valve(unsigned int _togglePin){
    if (_togglePin >= 0){
        //Set IO settings
        pinMode(_togglePin, OUTPUT);
        setPWMFrequency(_togglePin,1); //Frequency with divisor = 1; 31250Hz
        togglePin = _togglePin;
    }
    else{
        //Serial.println("Improper pin selected!");
        exit(1);
    }
}

Valve::~Valve(){}

void Valve::toggle(){
    toggle(!state);
    state = !state;
}

void Valve::toggle(bool _state){
    if (_state){ //ON
        analogWrite(togglePin, 255);
        unsigned long lastTime = millis();
        while(millis() - lastTime < (unsigned long)1000*64);
        analogWrite(togglePin, 127);
    }
    else{ //OFF
        analogWrite(togglePin,0); 
    }
    state = _state;
}

bool Valve::getState(){
    return state;
}

void Valve::setPWMFrequency(int pin, int divisor) {
    byte mode;
    switch(divisor) {
        case 1: mode = 0x01; break;
        case 8: mode = 0x02; break;
        case 64: mode = 0x03; break;
        case 256: mode = 0x04; break;
        case 1024: mode = 0x05; break;
        default: return;
    }
    if(pin == 13 || pin == 4) {
        TCCR0B = TCCR0B & 0b11111000 | mode;
    } else if (pin == 12 || pin == 11) {
        TCCR1B = TCCR1B & 0b11111000 | mode;
    } else if (pin == 10 || pin == 9) {
        TCCR2B = TCCR2B & 0b11111000 | mode;
    } else if (pin == 5 || pin == 3 || pin == 2) {
        TCCR3B = TCCR3B & 0b11111000 | mode;
    } else if (pin == 8 || pin == 7 || pin == 6) {
        TCCR4B = TCCR4B & 0b11111000 | mode;
    }
}
