#include "Heater.h"
#include "Test.h"
#include "TestQueue.h"
#include "O2-Cycler.h"
#include "Cartridge.h"

TestQueue* tests[NUM_CARTRIDGES];
int totalTime[NUM_CARTRIDGES]; //In seconds - time for all tests to complete (cartridge independent)
unsigned long dataTime = 0;
unsigned long setupTime = 0;

Test* currentTest[NUM_CARTRIDGES]; 
Cartridge* cartridges[NUM_CARTRIDGES];

void setup(){ 
    //Hardware Setup
    Serial.begin(115200);
    while(!Serial){delay(1);} //Wait for serial interface to initialize

    /******Setup for Timer0 Interrupt function******/
    TIMSK5 |= (1 << TOIE5);
    /***********************************************/
  
    //Check how many cartridges are loaded
    
    //Initialize and Check Sensors and Status for each cartridge (Get a baseline for any sensors that
    //are necessary). Create Cartridge Object.
    for (int i = 0; i < NUM_CARTRIDGES; i++){
      cartridges[i] = new Cartridge(i+1);
    }
    
    //Make a list of common or possible tests to complete

    //How long is the total experiment?
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
        for (int t = 0; t < totalTime[i]; t++){
            TestParameters* tp = new TestParameters();
            TestData* td = new TestData();
            TestOutputs* to = new TestOutputs();
            userInputTest(i,t,tp,td);
            Test* tes = new Test(to,tp,td);
            tests[i] = new TestQueue(tes);
            cartridges[i]->setTestQueue(tests[i]);  //Load TestQueue into each Cartridge
        }
    }
    //"Please start recording data!"
    setupTime = myMillis();
}

void loop(){
    for (int i = 0; i < NUM_CARTRIDGES; i++){
        //Data
        //readSensors();
        //outputData();
    
        //Control Decisions
        cartridges[i]->update();
        
    }
    //Update Display if available
    if ((myMillis() - dataTime) > 1000){
      int i = 0;
      Serial.print((myMillis()-setupTime)/1000.0);Serial.print(", ");
//      for (int i = 0; i < NUM_CARTRIDGES; i++){
//        Serial.print(cartridges[i]->getCurrentTest().getTestData()->cycles);Serial.print(", ");
//        Serial.print(cartridges[i]->getCurrentTest().getTestSetpoints()->temperature);Serial.print(", ");Serial.print(cartridges[i]->getCurrentTest().getTestSetpoints()->pressure);Serial.print(", ");

        if(cartridges[i]->getCurrentTest().getTestSetpoints()->desorbState){
          Serial.print("DESORBING");
        }
        else {
          Serial.print("ABSORBING");
        }
  
        Serial.print(", ");
        Serial.print(cartridges[i]->getCurrentTest().getTestSetpoints()->cycles);Serial.print(", ");
        Serial.print(cartridges[i]->getCurrentTest().getTestSetpoints()->temperature);Serial.print(", ");
        Serial.print(cartridges[i]->getCurrentTest().getTestSetpoints()->inPressure);Serial.print(", ");
        Serial.print(cartridges[i]->getCurrentTest().getTestSetpoints()->outPressure);Serial.print(", ");
        Serial.print(cartridges[i]->cartridgeSensors.getSensorData()->temperature);Serial.print(", ");Serial.print(cartridges[i]->cartridgeSensors.getSensorData()->heaterCurrent);Serial.print(", ");
        Serial.print(cartridges[i]->cartridgeSensors.getSensorData()->pGauge);Serial.print(", ");Serial.print(cartridges[i]->cartridgeSensors.getSensorData()->pAbs);Serial.print(", ");
//      }

      Serial.print(cartridges[0]->cartridgeSensors.getSensorData()->flow);Serial.print(", ");
      Serial.print(cartridges[0]->cartridgeSensors.getSensorData()->O2);Serial.print(", ");
      Serial.print(cartridges[0]->cartridgeSensors.getSensorData()->O2Temp);Serial.print(", ");      
      Serial.print(cartridges[0]->cartridgeSensors.getSensorData()->O2Comp);
      Serial.println(" ");
      dataTime = myMillis();
    }
}

void userInputTest(int cartridgeID, int timeint, TestParameters* tp, TestData* var){
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

unsigned long int myMillis(){
  return timer/490.46*1000;
}
