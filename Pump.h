#ifndef PUMP_H
#define PUMP_H

#include "O2-Cycler.h"

class Pump{
    unsigned int togglePin;
    bool state;

    public:
    Pump(unsigned int _togglePin);
    ~Pump();
    void toggle();
    void toggle(bool _state);
    bool getState();
};

#endif
