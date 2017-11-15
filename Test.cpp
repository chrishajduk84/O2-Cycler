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

    //Update Setpoints - Start with desorption state
    desorbState = true;
    mSetpoints.temperature = mSettings.desorpTemp;
    mSetpoints.outPressure = mSettings.outPressure;
    mSetpoints.inPressure = 0;

//    mSettings.minHeatingTime = 100000;
//    mSettings.minCoolingTime = 100000;
    
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

bool Test::update(CartridgeSensors* sensorData){
    //Check if test settings need to be changed (new test in the queue?)
    if (cycle > mSettings.cycles){
      return false; //Destroy current test object, alternatively raise a flag -Currently raising a flag
    }
    
    //Update Setpoints
    if (mSetpoints.desorbState){
      if ((sensorData->temperature >= mSetpoints.temperature)){// && (mData.stateTime >= mSettings.minHeatingTime)){
        //At the end of the desorption state, switch to absorption
        mSetpoints.desorbState = false;
        //Update Setpoints for ABSORPTION - Temperature, Pressure
        mSetpoints.temperature = mSettings.absorbTemp;
        mSetpoints.inPressure = mSettings.inPressure;
        mSetpoints.outPressure = 14.5;
      }
    }
    else if (!mSetpoints.desorbState){
      if ((sensorData->temperature <= mSetpoints.temperature)&& (false)){// && (mData.stateTime >= mSettings.minCoolingTime)){
        //At the end of the absorption state, add one cycle and switch to desorbtion
        cycle++;
        mSetpoints.desorbState = true;
        //Update Setpoints for DESORPTION - Temperature, Pressure
        mSetpoints.temperature = mSettings.desorpTemp;
        mSetpoints.outPressure = mSettings.outPressure;
        mSetpoints.inPressure = 0;
      }
    }
     
    /*====== OUTPUTS ======*/
    //Update Low Frequency thermal PWM controller based on parameters

    //Update Medium-Low Frequency Pumps 

    //Update High Frequency Valves
    
    return true;
}

