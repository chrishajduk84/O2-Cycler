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
    //Update Sensor Data
    cartridgeSensors.updateSensors();
    
    //Update TestQueue
    if (tQueue.size() <= 0){ //If the test queue is empty, put the cartridge in to a safe state and return
      pA.stopPWM();pB.stopPWM();heater.stopPWM();
      pA.toggle(false);pB.toggle(false);heater.toggle(false);
      vA.toggle(false);vB.toggle(false);vC.toggle(false);
      return; 
    }
    currentTest = tQueue.getCurrentTest();
    //TestSetpoints sensors;
    if (!currentTest->update(cartridgeSensors.getSensorData())){
      delete tQueue.pop(); //Delete Previous Test
      currentTest = tQueue.getCurrentTest(); //Start new test
      if (!currentTest) return; //If the test queue is empty, return
      
      //and switch control systems
      heaterPID.setSetpointSource(&currentTest->getTestSetpoints()->temperature);
      pumpAPID.setSetpointSource(&currentTest->getTestSetpoints()->inPressure);
      pumpBPID.setSetpointSource(&currentTest->getTestSetpoints()->outPressure);
    }
    //Update Control Systems
    heaterPID.update(myMillis() - lastLoopTime);
    pumpAPID.update(myMillis() - lastLoopTime);
    pumpBPID.update(myMillis() - lastLoopTime);
    if (currentTest->getTestSetpoints()->desorbState){
      vA.toggle(true);
      vB.toggle(false);   //This should be PWM'd to set backpressure
      vC.toggle(true);
    } else{
      vA.toggle(false);
      vB.toggle(false);   //This should be PWM'd to set backpressure
      vC.toggle(false);
    }
    
    lastLoopTime = myMillis();
}
Test Cartridge::getCurrentTest(){
  return *currentTest;
}


