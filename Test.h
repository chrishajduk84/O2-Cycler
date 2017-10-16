#ifndef TEST_H
#define TEST_H

typedef struct _TestMask{
    char cycles:1; //Default Value: true
    char absorbTemp:1; //Default Value: false
    char releaseTemp:1; //Default Value: false
    char inPressure:1; //Default Value: false
    char outPressure:1; //Default Value: false
    char heatingCurrent:1; //Default Value: false
    char heatingVoltage:1; //Default Value: false
    char maxHeatingTime:1; //Default Value: true
    char maxCoolingTime:1; //Default Value: true
    char minHeatingTime:1; //Default Value: false
    char minCoolingTIme:1; //Default Value: false
    char flow:1; //Default Value: false
} TestMask;

typedef struct _TestParameters{
    int cycles; //Default Value: 1
    float absorbTemp; //Default Value: 25
    float releaseTemp; //Default Value: 80C
    float inPressure; //Default Value: 8 psi
    float outPressure; //Default Value: 8 psi
    float heatingCurrent; //Default Value: 0.8A
    float heatingVoltage; //Default Value: 6V
    float maxHeatingTime; //Default Value: 3*60 seconds
    float maxCoolingTime; //Default Value: 3*60 seconds
    float minHeatingTime; //Default Value: 3*60 seconds
    float minCoolingTIme; //Default Value: 3*60 seconds
    float flow; //Default Value: 0.5 LPM
} TestParameters;

typedef struct _TestData{
    bool state;
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
  Test(TestMask* TM, TestParameters* setpoint, TestParameters* allowedVariance);
  void update();
};



#endif
