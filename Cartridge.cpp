#include "Cartridge.h"
#include <stdlib.h>

//These are static!!!
Cartridge* Cartridge::cList[NUM_CARTRIDGES];
unsigned int Cartridge::listLength;

//TODO:Temporary
float DEFAULT_VALUE = 0;
long lastLoopTime = 0;

Cartridge* Cartridge::getById(unsigned int id){
    if (id > 0)
        return cList[id-1];
    else
        return 0;
}

Cartridge::Cartridge(unsigned int id):heater(heaterPinout[id-1]),vA(vAPinout[id-1]),vB(vBPinout[id-1]),vC(vCPinout[id-1]),pA(pAPinout[id-1]),pB(pBPinout[id-1]),tQueue(),heaterPID(HEATER_UPDATE_PERIOD){
    //Assign a reference in a static array
    if (id <= NUM_CARTRIDGES){
        if (!cList[id-1]){
            cList[id-1] = this;
        }
        else{
            Serial.println("Initialized Cartridge Already Exists!");
            exit(1);
        }

        heaterPID.setSetpointSource(&DEFAULT_VALUE);
        heaterPID.setSensorSource(&DEFAULT_VALUE);
        heaterPID.setOutput(&heater,&heater.setPWM);

    //Do things with the queue?
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
    
    
    //Update TestQueue
    currentTest = tQueue.getCurrentTest();
    TestSetpoints sensors;
    if (!currentTest->update(&sensors)){
      //Start new test and switch control systems
      tQueue.pop();
      currentTest = tQueue.getCurrentTest();
      heaterPID.setSetpointSource(&currentTest->getTestSetpoints()->temperature);
    }

    //Update Control Systems
    heaterPID.update(millis() - lastLoopTime);
    lastLoopTime = millis();
}
