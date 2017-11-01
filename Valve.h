#ifndef VALVE_H
#define VALVE_H

#include "O2-Cycler.h"

class Valve{
    //static unsigned int pinList[NUM_CARTRIDGES];
    //static unsigned int listLength;
    unsigned int togglePin;
    bool state;
    void setPWMFrequency(int pin, int divisor);
    
    public:
    Valve(unsigned int _togglePin);
    ~Valve();
    void toggle();
    void toggle(bool _state);
    bool getState();
};

#endif
