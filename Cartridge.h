#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include "O2-Cycler.h"
#include "Heater.h"
#include "Valve.h"
#include "Pump.h"
#include "TestQueue.h"
#include "PID.h"
//#include "BangBang.h"
#include "Sensors.h"

#define HEATER_UPDATE_PERIOD 1000
#define PUMP_UPDATE_PERIOD 1000

class Cartridge{
    static Cartridge* cList[NUM_CARTRIDGES];
    static unsigned int listLength;
    Test* currentTest;
    unsigned int cID;
    float heaterK[5] = {1000,1e-4,1,0,0};
    float pumpAK[5] = {100,1e-4,1,0,0};
    float pumpBK[5] = {-100,1e-4,1,0,0};
    long lastLoopTime = 0;
    
    public:
    Heater heater;
    PID<Heater> heaterPID;
    Valve vA; //2 Way
    Valve vB; //2 Way
    Valve vC; //3 Way
    Pump pA;    //Pressure
    PID<Pump> pumpAPID;
    Pump pB;    //Vacuum
    PID<Pump> pumpBPID;
    Sensors cartridgeSensors; //All Sensors
    TestQueue tQueue;
    static Cartridge* getById(unsigned int id);
    Cartridge(unsigned int id);
    ~Cartridge();
    void setTestQueue(TestQueue* tq);
    void update();
    Test getCurrentTest();
};

#endif
