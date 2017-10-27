#include "Test.h"

TestOutputs mTO;
TestParameters mSettings;
TestData mSensors;
TestData mData;

bool desorpState = false;
int cycle = 0;


Test::Test(TestOutputs* outputs, TestParameters* settings, TestData* sensors){
         
    //Check TestMask to ensure there is a valid combination of test parameters

    //If test is not valid, ask for confirmation on assumptions
    
    //Save Parameters
    mTO = *outputs;
    mSettings = *settings;
    mSensors = *sensors;

    //Initialize PIDs
//    heaterPID.setSetpointSource(&TEMPORARY_HARDCODED_VALUE); //This will come from the settings
//    heaterPID.setSensorSource(&TEMPORARY_HARDCODED_VALUE2); //This will come from some Sensor Object
//    heaterPID.setOutput(outputs->heater); //This will be passed in

    //TODO:OTHER COMPONENTS INITIALIZED
    //pumpPID.setSetpointSource();
    
    
}

bool Test::update(TestParameters* data){
    //Check if test settings need to be changed (new test in the queue?)
    if (cycle > mSettings.cycles){
      return false; //Destroy current test object, alternatively raise a flag
    }
        
    //Get Sensor Readings
    
    
    /*====== OUTPUTS ======*/
    //Update Low Frequency thermal PWM controller based on parameters

    //Update Medium-Low Frequency Pumps 

    //Update High Frequency Valves
    
    return true;
}

