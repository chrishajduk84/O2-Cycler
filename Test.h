#ifndef TEST_H
#define TEST_H

#include "PID.h"
#include "Sensors.h"

#define HEATER_UPDATE 1000
#define PUMP_UPDATE 200

typedef struct _TestOutputs{ //These contain function pointers //THIS MAYBE DEPRECIATED/REMOVED
    void* (*heater)(int);
    void* (*inPump)(int);
    void* (*outPump)(int);
    void* (*valve3)(int);
    void* (*valve2A)(int);
    void* (*valve2B)(int);
} TestOutputs;

typedef struct _TestParameters{
    int cycles; //Default Value: 1
    float absorbTemp; //Default Value: 25
    float desorpTemp; //Default Value: 80C
    float inPressure; //Default Value: 8 psi
    float outPressure; //Default Value: 8 psi
    float heatingPower; //Default Value: 0.8A*12V = 9.6W
    float maxHeatingTime; //Default Value: 3*60 seconds
    float maxCoolingTime; //Default Value: 3*60 seconds
    float minHeatingTime; //Default Value: 3*60 seconds
    float minCoolingTime; //Default Value: 3*60 seconds
    //float flow; //Default Value: 0.5 LPM
} TestParameters;

typedef struct _TestSetpoints{
    int cycles;
    float temperature;
    float inPressure;
    float outPressure;
    bool desorbState;
} TestSetpoints;
/*typedef struct _TestSensors{
    float temperature;
    float inPressure;
    float outPressure;
    float heatingCurrent;
    float heatingVoltage;
    float stateTime;
    float totalTime;
    float flow;
} TestSensors;*/

typedef struct _TestData{
    bool state; //True = desorb, false = absorb
    int cycles;
    float temperature;
    float inPressure;
    float outPressure;
    float heatingCurrent;
    float heatingVoltage;
    float stateTime;
    float totalTime;
    float flow;
} TestData;

class Test{
  public:
  Test(TestOutputs* outputs, TestParameters* setpoint, TestData* sensors);
  TestOutputs* getTestOutputs();
  TestParameters* getTestParameters();
  TestSetpoints* getTestSetpoints();
  TestData* getTestData();
  bool update(CartridgeSensors* sensorData);
};



#endif
