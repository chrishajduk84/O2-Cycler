#include "Test.h"

TestMask mTM;
TestParameters mSetpoint;
TestParameters mAllowedVariance;
TestData mData;
Test::Test(TestMask* TM, TestParameters* setpoint, TestParameters* allowedVariance){
         
    //Check TestMask to ensure there is a valid combination of test parameters

    //If test is not valid, ask for confirmation on assumptions
    
    //Save Parameters
}

void Test::update(){
    //Check if test settings need to be changed (new test in the queue?)
       
    //Get Sensor Readings
    //readSensors();
    //Update BangBang thermal controller based on parameters
        
    //Update Valves
       
    //Update Pumps
        
    return mData;
}

