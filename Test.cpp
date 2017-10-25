#include "Test.h"

TestMask mTM;
TestParameters mSettings;
TestParameters mAllowedVariance;
TestData mData;

bool desorpState = false;
int cycle = 0;

Test::Test(TestMask* TM, TestParameters* settings, TestParameters* allowedVariance){
         
    //Check TestMask to ensure there is a valid combination of test parameters

    //If test is not valid, ask for confirmation on assumptions
    
    //Save Parameters
    mTM = *TM;
    mSettings = *settings;
    mAllowedVariance = *allowedVariance;
}

void Test::update(){
    //Check if test settings need to be changed (new test in the queue?)
    if (cycle > mSettings.cycles){
      delete this; //Destroy current test object, alternatively raise a flag
    }
    
    //Get Sensor Readings
    //readSensors();

    
    //Update BangBang thermal controller based on parameters
    
    //Update Valves
       
    //Update Pumps
        
    return mData;
}


