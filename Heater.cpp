#include "Heater.h"
#include "Pump.h"
#include <stdlib.h>

//These are static!!!
unsigned int Heater::pinList[NUM_CARTRIDGES];
unsigned int Heater::listLength;
Heater* Heater::heaterList[NUM_CARTRIDGES];

/* NOTE: THIS IS A PWM HACK */
unsigned long int timer = 0;
ISR(TIMER5_OVF_vect)   // timer compare interrupt service routine
{
  timer += 1;
  /************HEATER****************/
  for (int i = 0; i < Heater::listLength; i++){
    if (Heater::heaterList[i]->pwm){
      if (timer%100 < ((Heater::heaterList[i]->duty)*Heater::heaterList[i]->heatingFactor)){
        Heater::heaterList[i]->toggle(true);
      }
      else{
        Heater::heaterList[i]->toggle(false);
      }
    }
  }
  
  /************PUMP****************/
  for (int i = 0; i < Pump::listLength; i++){
    if (Pump::pumpList[i]->pwm){
      if (timer%100 < Pump::pumpList[i]->duty){
        Pump::pumpList[i]->toggle(true);
      }
      else{
        Pump::pumpList[i]->toggle(false);
      }
    }
  }
}
/****************************/

Heater::Heater(unsigned int _togglePin){
    //Assign the heating pin to the object
    for (int i = 0; i < listLength; i++){
        if (pinList[i] == _togglePin){
            exit(1);
        }
    }
    //If the heating pin hasn't already been initialized, add it to the list
    heaterList[listLength] = this;
    pinMode(_togglePin, OUTPUT);
    pinList[listLength++] = togglePin = _togglePin;
}

/*Heater::Heater(unsigned int _togglePi, unsigned int _currentPin){
    Heater(_togglePi);
    currentPin = _currentPin;
}

Heater::Heater(unsigned int _togglePin, unsigned int _currentPin, unsigned int _voltagePin){
    Heater(_togglePin, _currentPin);
    voltagePin = _voltagePin;
}*/

Heater::~Heater(){
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

float Heater::getVoltage(){
    return analogRead(voltagePin)*5.0/1024; //TODO
}

float Heater::getCurrent(){
    return analogRead(currentPin)*5.0/1024/CURRENT_RESISTOR; //TODO
}

float Heater::getPower(){
    return getVoltage()*getCurrent();
}

float Heater::getTemperatureEstimate(){ //For the core of the wire
    return 0; //TODO:Need model for nichrome power -> heat generated -> Temperature
                // Need an understanding of the environment for this to work.
                // Thermal conductivity, heat capacity and resistivity of the
                // nichrome (including length)
                // Kalman filter??????
}

void Heater::addCurrentPin(unsigned int _currentPin){
    currentPin = _currentPin;
}

void Heater::addVoltagePin(unsigned int _voltagePin){
    voltagePin = _voltagePin;
}

void Heater::toggle(){
    digitalWrite(togglePin, !state);
    state = !state;
}

void Heater::toggle(bool _state){
    digitalWrite(togglePin, _state);
    state = _state;
}

bool Heater::getState(){
    return state;
}

void Heater::setPWM(int _duty){ //Hacks not really (hardware) PWM
  pwm = true;
  duty = _duty;
}

void Heater::stopPWM(){ //Hacks not really PWM
  pwm = false;
}

void Heater::setMaxPower(float _heatingFactor){
  heatingFactor = _heatingFactor;
}

