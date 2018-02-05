#include "Test.h"

Test::Test(TestParameters* settings){
         
    //Check TestMask to ensure there is a valid combination of test parameters

    //If test is not valid, ask for confirmation on assumptions
    
    //Save Parameters
    mSettings = *settings;

    mSetpoints.cycleState = ABSORB;
    //Update Setpoints for ABSORPTION - Temperature, Pressure
    mSetpoints.temperature = mSettings.absorbTemp;
    mSetpoints.inPressure = mSettings.inPressure;
    mSetpoints.outPressure = 14.5;
    mData.stateTime = 0;
    beginStateTime = myMillis()/1000.0;
    
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
    if (mSetpoints.cycles >= mSettings.cycles){
      return false; //Destroy current test object, alternatively raise a flag -Currently raising a flag, then destroying object
    }

    if (mSetpoints.cycleState == ABSORB){
      //SWITCHING CONDITIONS - At the end of the absorption state switch to the intermediate state
      if ((sensorData->temperature <= mSetpoints.temperature) && (mData.stateTime >= mSettings.minCoolingTime)){
        mSetpoints.cycleState = INTERMEDIATE_A;
        //Update Setpoints for INTERMEDIATE_A - Temperature, Pressure
        mSetpoints.temperature = mSettings.desorpTemp;
        mSetpoints.outPressure = mSettings.outPressure;
        mSetpoints.inPressure = 0;
        //Reset Timer
        beginStateTime = myMillis()/1000.0;
      }
    }
    else if (mSetpoints.cycleState == INTERMEDIATE_A){ //The purpose of this is to pump down the cartridge
      if (sensorData->pOutlet <= mSetpoints.outPressure){
        mSetpoints.cycleState = INTERMEDIATE_B;
        //Update Setpoints for INTERMEDIATE_B - Temperature, Pressure
        mSetpoints.temperature = mSettings.desorpTemp;
        mSetpoints.outPressure = mSettings.outPressure;
        mSetpoints.inPressure = 0;
        //Reset Timer
        beginStateTime = myMillis()/1000.0;
      }
    }
    else if (mSetpoints.cycleState == INTERMEDIATE_B){ //The purpose of this is to seal it until it is ready to desorb (temperature-wise)
      
      if (sensorData->temperature >= mSetpoints.temperature - HEATING_EPSILON){
        mSetpoints.cycleState = DESORB;
        //Update Setpoints for DESORPTION - Temperature, Pressure
        mSetpoints.temperature = mSettings.desorpTemp;
        mSetpoints.outPressure = mSettings.outPressure;
        mSetpoints.inPressure = 0;
        //Reset Timer
        beginStateTime = myMillis()/1000.0;
      }
    }
    else if (mSetpoints.cycleState == DESORB){
      //SWITCHING CONDITIONS - At the end of the desorption state, switch to absorption
      if ((sensorData->temperature >= mSetpoints.temperature) && (mData.stateTime >= mSettings.minHeatingTime)){
        mSetpoints.cycles++;
        mSetpoints.cycleState = ABSORB;
        //Update Setpoints for ABSORBTION - Temperature, Pressure
        mSetpoints.temperature = mSettings.absorbTemp;
        mSetpoints.inPressure = mSettings.inPressure;
        mSetpoints.outPressure = 14.5;
        //Reset Timer
        beginStateTime = myMillis()/1000.0;
      }
    }
    else {
          beginStateTime = myMillis()/1000.0;
          //Update Setpoints - Start with absorption state
           //mSetpoints.cycleState = ABSORB;
          
    }
    
    mData.stateTime = myMillis()/1000.0 - beginStateTime;
    
    return true;
}
