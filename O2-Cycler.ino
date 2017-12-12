#include "Heater.h"
#include "Test.h"
#include "TestQueue.h"
#include "O2-Cycler.h"
#include "Cartridge.h"
#include <string.h>

TestQueue* tests[NUM_CARTRIDGES];
int totalTime[NUM_CARTRIDGES]; //In seconds - time for all tests to complete (cartridge independent)
unsigned long dataTime = 0;
unsigned long setupTime = 0;

Test* currentTest[NUM_CARTRIDGES]; 
Cartridge* cartridges[NUM_CARTRIDGES];

void userInputTest(int cartridgeID, int timeint, TestParameters* tp){
  char buf[100];
  sprintf(buf, "Cartridge:%d - Interval:%d, Specify the parameters:",cartridgeID + 1, timeint);
  Serial.println(buf);
  
  tp->cycles = questionValue("How many cycles? (#)").toInt();
  tp->desorpTemp = questionValue("What is the desorption temperature? (°C)").toFloat();
  tp->absorbTemp = questionValue("What is the absorption temperature? (°C)").toFloat();
  tp->heatingPower = questionValue("What is the heating power? (0 - 1.0)").toFloat();
  tp->inPressure = questionValue("What is the inlet pressure? (relative psi)").toFloat();
  tp->outPressure = questionValue("What is the outlet pressure? (relative psi)").toFloat();
  tp->minHeatingTime = questionValue("What is the minimum heating time? (seconds)").toFloat();
  tp->minCoolingTime = questionValue("What is the minimum cooling time? (seconds)").toFloat();
  tp->maxHeatingTime = 3*60;
  tp->maxCoolingTime = 3*60;
}

String questionValue(String question){
  String tmp = "";
  Serial.print(question);
  while (tmp == ""){if (Serial.available() > 0)tmp = Serial.readString();}
  Serial.println(tmp);
  return tmp;
}

void setTests(){
  if (Serial.available() > 0){
    //Parse input string:
    //Cartridge #, # of tests (n),{Test cycles, Desorp Temp, Absorp Temp, Power, Inlet Pressure, Outlet Pressure, Min Heating Time, Min Cooling Time}*n, checksum
    String str = Serial.readString();
    
    //Check for errors
    byte checksum = 0;
    const char* strArr = str.c_str();
    int comma = 0;
    for (int i = 0; i < str.length() - 1; i++){
      if (strArr[i] == ',') comma++; //There are comma+1 fields
    }
    
    float inputData[comma+1];
    int counter = 0;
    int pos = 0;
    int lastpos = -1;
    while((pos = str.indexOf(',', pos+1)) != -1){
      inputData[counter] = str.substring(lastpos+1,pos).toFloat();
      checksum ^= (int)inputData[counter] & 0xFF;
      lastpos = pos;
      counter++;
    }
    inputData[counter] = str.substring(lastpos+1,str.length()-1).toFloat();
        
    if (checksum != inputData[comma] && inputData[comma] != 0xFF){
      return;
    }

    //Set variables
    int numCartridge = (int)inputData[0];
    int nTests = (int)inputData[1];
    TestParameters* tp;
    TestQueue* tests = new TestQueue();

    for (int n = 0; n < nTests; n++){      
        tp = new TestParameters();
        tp->cycles = (int)inputData[n*8+2];
        tp->desorpTemp = inputData[n*8+3];
        tp->absorbTemp = inputData[n*8+4];
        tp->heatingPower = inputData[n*8+5];
        tp->inPressure = inputData[n*8+6];
        tp->outPressure = inputData[n*8+7];
        tp->minHeatingTime = inputData[n*8+8];
        tp->minCoolingTime = inputData[n*8+9];
        tp->maxHeatingTime = 3*60;
        tp->maxCoolingTime = 3*60;
        Test* tes = new Test(tp);
        tests->addTest(tes);
    }
    cartridges[numCartridge-1]->setTestQueue(tests);
  }
}

unsigned long int myMillis(){
  return timer/490.46*1000;
}

void setup(){ 
    //Hardware Setup
    Serial.begin(115200);
    while(!Serial){delay(1);} //Wait for serial interface to initialize
  
    //Check how many cartridges are loaded
    
    //Initialize and Check Sensors and Status for each cartridge (Get a baseline for any sensors that
    //are necessary). Create Cartridge Object.
    for (int i = 0; i < NUM_CARTRIDGES; i++){
      cartridges[i] = new Cartridge(i+1);
    }
    
    //Make a list of common or possible tests to complete

    /*//How long is the total experiment?
    for (int i = 0; i < NUM_CARTRIDGES; i++){
      char buf[70];sprintf(buf,"Cartridge %d: How many times will the parameters change?", i+1);
      Serial.print(buf);
      String runtime = "";
      while (runtime == ""){if (Serial.available() > 0)runtime = Serial.readString();}
      totalTime[i] = runtime.toInt();
      Serial.println(totalTime[i]);
    }
    
    //Generate Test Objects - User chooses the tests to run
    for (int i = 0; i < NUM_CARTRIDGES; i++){
        tests[i] = new TestQueue();
        for (int t = 0; t < totalTime[i]; t++){
            TestParameters* tp = new TestParameters();
            userInputTest(i,t,tp);
            Test* tes = new Test(tp);
            tests[i]->addTest(tes);
        }
        cartridges[i]->setTestQueue(tests[i]);  //Load TestQueue into each Cartridge
    }*/
    
    //"Please start recording data!"
    setupTime = myMillis();
    
    /******Setup for Timer0 Interrupt function******/
    TIMSK5 |= (1 << TOIE5);
    /***********************************************/
}

void loop(){
    setTests();
  
    for (int i = 0; i < NUM_CARTRIDGES; i++){
        //Data
        //readSensors();
        //outputData();
    
        //Control Decisions
        cartridges[i]->update();
        
    }
    //Update Display if available
    if ((myMillis() - dataTime) > 1000){
      Serial.print((myMillis()-setupTime)/1000.0);Serial.print(", ");
      for (int i = 0; i < NUM_CARTRIDGES; i++){
        Serial.print("C");Serial.print(i+1);Serial.print(": ");
        if(cartridges[i]->getCurrentTest().getTestSetpoints()->cycleState == DESORB){
          Serial.print("DESORBING");
        }
        else if (cartridges[i]->getCurrentTest().getTestSetpoints()->cycleState == INTERMEDIATE_A){
          Serial.print("INTERME_A");
        }
        else if (cartridges[i]->getCurrentTest().getTestSetpoints()->cycleState == INTERMEDIATE_B){
          Serial.print("INTERME_B");
        }
        else if (cartridges[i]->getCurrentTest().getTestSetpoints()->cycleState == ABSORB) {
          Serial.print("ABSORBING");
        }
        else if (cartridges[i]->getCurrentTest().getTestSetpoints()->cycleState == INVALID) {
          Serial.print("INVALID");
        }
  
        Serial.print(", ");
        Serial.print(cartridges[i]->getCurrentTest().getTestSetpoints()->cycles);Serial.print(", ");
        Serial.print(cartridges[i]->getCurrentTest().getTestSetpoints()->temperature);Serial.print(", ");
        Serial.print(cartridges[i]->getCurrentTest().getTestSetpoints()->inPressure);Serial.print(", ");
        Serial.print(cartridges[i]->getCurrentTest().getTestSetpoints()->outPressure);Serial.print(", ");
        Serial.print(cartridges[i]->cartridgeSensors.getSensorData()->temperature);Serial.print(", ");Serial.print(cartridges[i]->cartridgeSensors.getSensorData()->heaterCurrent);Serial.print(", ");
        Serial.print(cartridges[i]->cartridgeSensors.getSensorData()->pInlet);Serial.print(", ");Serial.print(cartridges[i]->cartridgeSensors.getSensorData()->pOutlet);Serial.print(", ");
        Serial.print(cartridges[i]->cartridgeSensors.getSensorData()->flow);Serial.print(", ");
      }
      Serial.print(cartridges[0]->cartridgeSensors.getSensorData()->O2);Serial.print(", ");
      Serial.print(cartridges[0]->cartridgeSensors.getSensorData()->O2Temp);Serial.print(", ");      
      Serial.print(cartridges[0]->cartridgeSensors.getSensorData()->O2Comp);
      Serial.println(" ");
      dataTime = myMillis();
    }
}
