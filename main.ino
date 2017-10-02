//#include

#define NUM_CARTRIDGES 3

void setup(){
    //Initialize and Check Sensors and Status (Get a baseline for any sensors that
    //are necessary)
     
    //Check how many cartridges are loaded
    
    //Make a list of common or possible tests to complete
    
    //Generate Test Objects - Choose the test to run
    TestQueue tests[NUM_CARTRIDGES];
    for (int i = 0; i < NUM_CARTRIDGES; i++){
        for (int t = 0; t < tStep[i]; t++){
            TestMask tm = new TestMask();
            TestParameters tp = new TestParameters();
            TestParameters var = new TestParameters();
            Test t = new Test(tm,tp,var)
            tests[i] = new TestQueue(t);
        }
    }
    
    //"Please start recording data!"
    
}

void loop(){
    for (int i = 0; i < NUM_CARTRIDGES; i++){
        //Data
        readSensors();
        outputData();
        
        //Control Decisions
        Test.update();
        
          
    }
    
    //Update Display if available
}
