#ifndef TEST_H
#define TEST_H

#include "O2-Cycler.h"
#include "PID.h"
#include "Sensors.h"

//Due to comparisons between float values - Defines allowance for temperature inaccuracy 0.1Celsius
#define HEATING_EPSILON 0.1

typedef enum _CycleState{
  INVALID = -1,
  ABSORB = 0,
  INTERMEDIATE_A = 1,
  INTERMEDIATE_B = 2,
  DESORB = 3,
  INTERMEDIATE_C = 4
} CycleState;

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
    CycleState cycleState;
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
  float beginStateTime = 0;
  TestParameters mSettings = {};
  TestSetpoints mSetpoints = {};
  TestData mData = {};

  public:
  Test(TestParameters* setpoint);
  TestParameters* getTestParameters();
  TestSetpoints* getTestSetpoints();
  TestData* getTestData();
  bool update(CartridgeSensors* sensorData);
};

#endif
