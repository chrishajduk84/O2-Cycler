#ifndef PUMP_H
#define PUMP_H

#include "O2-Cycler.h"

class Pump{
    static unsigned int pinList[NUM_CARTRIDGES*2];
    unsigned int togglePin;
    bool state;    

    public:
    int duty;
    bool pwm = false;
    static unsigned int listLength;
    static Pump* pumpList[NUM_CARTRIDGES*2];
    Pump(unsigned int _togglePin);
    ~Pump();
    void toggle();
    void toggle(bool _state);
    bool getState();
    void setPWM(int _duty); //Hacks not really (hardware) PWM
    void stopPWM();
};

#endif
