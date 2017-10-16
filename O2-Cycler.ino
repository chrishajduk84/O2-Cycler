#include "Test.h"
#include "TestQueue.h"

#define NUM_CARTRIDGES 3

TestQueue* tests[NUM_CARTRIDGES];
int totalTime[NUM_CARTRIDGES]; //In seconds - time for all tests to complete (cartridge independent)

Test* currentTest[NUM_CARTRIDGES];
    
void setup(){
    //Initialize and Check Sensors and Status (Get a baseline for any sensors that
    //are necessary)
    
    //Check how many cartridges are loaded
    
    //Make a list of common or possible tests to complete

    //How long is the total experiment?
    for (int i = 0; i < NUM_CARTRIDGES; i++){
      totalTime[i] = 120;
    }
    //Generate Test Objects - User chooses the tests to run
    for (int i = 0; i < NUM_CARTRIDGES; i++){
        for (int t = 0; t < totalTime[i]; t++){
            TestMask* tm = new TestMask();
            TestParameters* tp = new TestParameters();
            TestParameters* var = new TestParameters();
            Test* tes = new Test(tm,tp,var);
            tests[i] = new TestQueue(tes);
        }
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
