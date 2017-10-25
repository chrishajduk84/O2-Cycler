#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include "O2-Cycler.h"
#include "Heater.h"
#include "Valve.h"
#include "Pump.h"
#include "TestQueue.h"

class Cartridge{
    static Cartridge* cList[NUM_CARTRIDGES];
    static unsigned int listLength;
    
    public:
    Heater heater;
    Valve vA; //2 Way
    Valve vB; //2 Way
    Valve vC; //3 Way
    Pump pA;    //Pressure
    Pump pB;    //Vacuum
    TestQueue tQueue;
    static Cartridge* getById(unsigned int id);
    Cartridge(unsigned int id);
    ~Cartridge();
    void setTestQueue(TestQueue* tq);
    void update(); 
};

#endif
