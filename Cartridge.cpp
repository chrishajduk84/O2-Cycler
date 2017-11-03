#include "Cartridge.h"
#include <stdlib.h>

//These are static!!!
Cartridge* Cartridge::cList[NUM_CARTRIDGES];
unsigned int Cartridge::listLength;

long lastLoopTime = 0;

Cartridge* Cartridge::getById(unsigned int id){
    if (id > 0)
        return cList[id-1];
    else
        return 0;
}

Cartridge::Cartridge(unsigned int id):heater(heaterPinout[id-1]),vA(vAPinout[id-1]),vB(vBPinout[id-1]),vC(vCPinout[id-1]),pA(pAPinout[id-1]),pB(pBPinout[id-1]),cartridgeSensors(id-1){
    //Assign a reference in a static array
    if (id <= NUM_CARTRIDGES){
        if (!cList[id-1]){
            cList[id-1] = this;
        }
        else{
            Serial.println("Initialized Cartridge Already Exists!");
            exit(1);
        }

        heaterPID.setSensorSource(&cartridgeSensors.getSensorData()->temperature);
        heaterPID.setOutput(&heater,&heater.setPWM);
        heaterPID.setGain(heaterK);
        pumpAPID.setSensorSource(&cartridgeSensors.getSensorData()->pGauge); //Positive Pressure Sensor
        pumpAPID.setOutput(&pA,&pA.setPWM);
        pumpAPID.setGain(pumpAK);
        pumpBPID.setSensorSource(&cartridgeSensors.getSensorData()->pAbs);//Absolute Pressure Sensor
        pumpBPID.setOutput(&pB,&pB.setPWM);
        pumpBPID.setGain(pumpBK);
        cID = id;
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
  currentTest = tQueue.getCurrentTest();
  heaterPID.setSetpointSource(&currentTest->getTestSetpoints()->temperature);
  pumpAPID.setSetpointSource(&currentTest->getTestSetpoints()->inPressure);
  pumpBPID.setSetpointSource(&currentTest->getTestSetpoints()->outPressure);
}

void Cartridge::update(){
//    Serial.print("Cart:");Serial.println(cID);
    //Update Sensor Data
    cartridgeSensors.updateSensors();
    
    //Update TestQueue
    currentTest = tQueue.getCurrentTest();
    //TestSetpoints sensors;
    if (!currentTest->update(cartridgeSensors.getSensorData())){
      delete tQueue.pop(); //Delete Previous Test
      currentTest = tQueue.getCurrentTest(); //Start new test

      //and switch control systems
      heaterPID.setSetpointSource(&currentTest->getTestSetpoints()->temperature);
      pumpAPID.setSetpointSource(&currentTest->getTestSetpoints()->inPressure);
      pumpBPID.setSetpointSource(&currentTest->getTestSetpoints()->outPressure);
    }
    //Update Control Systems
    heaterPID.update(millis() - lastLoopTime);
    pumpAPID.update(millis() - lastLoopTime);
    pumpBPID.update(millis() - lastLoopTime);
    lastLoopTime = millis();

}

Test Cartridge::getCurrentTest(){
  return *currentTest;
}

