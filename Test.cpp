#include "Test.h"

TestOutputs mTO;
TestParameters mSettings;
TestSetpoints mSetpoints;
TestData mSensors;
TestData mData;

bool desorbState = false;
int cycle = 0;
float temperature = 0;

Test::Test(TestOutputs* outputs, TestParameters* settings, TestData* sensors){
         
    //Check TestMask to ensure there is a valid combination of test parameters

    //If test is not valid, ask for confirmation on assumptions
    
    //Save Parameters
    mTO = *outputs;
    mSettings = *settings;
    mSensors = *sensors;
    
    
}

TestOutputs* Test::getTestOutputs(){
  return &mTO;
}

TestParameters* Test::getTestParameters(){
  return &mSettings;
}

TestSetpoints* Test::getTestSetpoints(){ //Affected by the state
  return &mSetpoints;
}

TestData* Test::getTestData(){
  return &mData;
}

bool Test::update(TestSetpoints* sensorData){
    //Check if test settings need to be changed (new test in the queue?)
    if (cycle > mSettings.cycles){
      return false; //Destroy current test object, alternatively raise a flag
    }
    
    //Update Setpoints
    if (desorbState){
      if (sensorData->temperature >= mSetpoints.temperature){// && mData->stateTime >= mSettings->minHeatingTime){
        //At the end of the desorption state, switch to absorption
        desorbState = false;
        //Update Setpoints - Temperature, Pressure
        mSetpoints.temperature = mSettings.absorbTemp;
      }
    }
    else if (!desorbState){
      if (sensorData->temperature <= mSetpoints.temperature){ // && mData->stateTime >= mSettings->minCoolingTime){
        //At the end of the absorption state, add one cycle and switch to desorbtion
        cycle++;
        desorbState = true;
        //Update Setpoints - Temperature, Pressure
        mSetpoints.temperature = mSettings.desorpTemp;
      }
    }
     
    /*====== OUTPUTS ======*/
    //Update Low Frequency thermal PWM controller based on parameters

    //Update Medium-Low Frequency Pumps 

    //Update High Frequency Valves
    
    return true;
}

