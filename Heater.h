#ifndef HEATER_H
#define HEATER_H

#include "O2-Cycler.h"

#define CURRENT_RESISTOR 0.01

class Heater{
    static unsigned int pinList[NUM_CARTRIDGES];
    unsigned int togglePin;
    unsigned int currentPin; //To detect how much current is being drawn by the heater - Optional
    unsigned int voltagePin; //To detect what voltage is being used - Optional
    bool state;
    
    public:
    bool pwm = false;
    int duty;
    float heatingFactor = 1;
    static unsigned int listLength;
    static Heater* heaterList[NUM_CARTRIDGES];
    Heater(unsigned int _togglePin);
    ~Heater();
    float getVoltage();
    float getCurrent();
    float getPower();
    float getTemperatureEstimate();
    void addCurrentPin(unsigned int _currentPin);
    void addVoltagePin(unsigned int _voltagePin);
    void toggle();
    void toggle(bool _state);
    bool getState();
    void setPWM(int _duty); //Hacks not really PWM
    void stopPWM(); //Hacks not really PWM
    void setMaxPower(float heatingFactor);
};

#endif
