#include "Cartridge.h"
#include <stdlib.h>

//These are static!!!
Cartridge* Cartridge::cList[NUM_CARTRIDGES];
unsigned int Cartridge::listLength;

Cartridge* Cartridge::getById(unsigned int id){
    if (id > 0)
        return cList[id-1];
    else
        return 0;
}

Cartridge::Cartridge(unsigned int id):heater(heaterPinout[id-1]),vA(vAPinout[id-1]),vB(vBPinout[id-1]),vC(vCPinout[id-1]),pA(pAPinout[id-1]),pB(pBPinout[id-1]),tQueue(){
    //Assign a reference in a static array
    if (id <= NUM_CARTRIDGES){
        if (!cList[id-1]){
            cList[id-1] = this;
        }
        else{
            //Serial.println("Initialized Cartridge Already Exists!");
            exit(1);
        }
    }
}

Cartridge::~Cartridge(){
    //Remove all entries in static variables
    for (int i = 0; i < listLength; i++){
        if (cList[i] == this){
            cList[i] = 0;
            break;
        }
    }
}

void Cartridge::setTestQueue(TestQueue* tq){
  tQueue = *tq;
}

void Cartridge::update(){
    //Update Sensor Data

    //Update Control Systems

    //Update TestQueue
}
