#include "Heater.h"
#include "Test.h"
#include "TestQueue.h"
#include "O2-Cycler.h"
#include "Cartridge.h"

TestQueue* tests[NUM_CARTRIDGES];
int totalTime[NUM_CARTRIDGES]; //In seconds - time for all tests to complete (cartridge independent)

Test* currentTest[NUM_CARTRIDGES]; 
Cartridge* cartridges[NUM_CARTRIDGES];

void setup(){ 
    Serial.begin(115200);
  
    //Check how many cartridges are loaded

    //Initialize and Check Sensors and Status for each cartridge (Get a baseline for any sensors that
    //are necessary). Create Cartridge Object.
    for (int i = 0; i < NUM_CARTRIDGES; i++){
      cartridges[i] = new Cartridge(i);
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
            TestMask* tm = new TestMask();
            TestParameters* tp = new TestParameters();
            TestParameters* var = new TestParameters();
            userInputTest(i,t,tm,tp,var);
            Test* tes = new Test(tm,tp,var);
            tests[i] = new TestQueue(tes);
        }
    }
    
    //Load TestQueue into each Cartridge
    for (int i = 0; i < NUM_CARTRIDGES; i++){
      cartridges[i]->setTestQueue(tests[i]);
    }
    
    //"Please start recording data!"
}

void loop(){
    for (int i = 0; i < NUM_CARTRIDGES; i++){
        //Data
        //readSensors();
        //outputData();
        
        //Control Decisions
        currentTest[i]->update();
                
    }
    
    //Update Display if available
}

void userInputTest(int cartridgeID, int timeint, TestMask* tm, TestParameters* tp, TestParameters* var){
  char buf[100];
  sprintf(buf, "Cartridge:%d - Interval:%d, Specify the parameters:",cartridgeID + 1, timeint);
  Serial.println(buf);
  
  tp->cycles = questionValue("How many cycles? (#)").toInt();
  tp->desorpTemp = questionValue("What is the desorption temperature? (°C)").toFloat();
  tp->absorbTemp = questionValue("What is the absorption temperature? (°C)").toFloat();
  tp->heatingPower = questionValue("What is the heating power? (W, max=12.0)").toFloat();
  tp->inPressure = questionValue("What is the inlet pressure? (psi)").toFloat();
  tp->outPressure = questionValue("What is the outlet pressure? (psi)").toFloat();

  tp->maxHeatingTime = 3*60;
  tp->maxCoolingTime = 3*60;

  tm->cycles = true;
  tm->desorpTemp = true;
  tm->absorbTemp = true;
  tm->heatingPower = true;
  tm->inPressure = true;
  tm->outPressure = true;
  tm->maxHeatingTime = true;
  tm->maxCoolingTime = true;
  tm->minHeatingTime = false;
  tm->minCoolingTime = false;  
}

String questionValue(String question){
  String tmp = "";
  Serial.print(question);
  while (tmp == ""){if (Serial.available() > 0)tmp = Serial.readString();}
  Serial.println(tmp);  
  return tmp;
}

