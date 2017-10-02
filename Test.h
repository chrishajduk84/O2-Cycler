#ifndef TEST_H
#define TEST_H

typedef struct _TestMask{
    char cycles:1 = true;
    char absorbTemp:1 = false;
    char releaseTemp:1 = false;
    char inPressure:1 = false;
    char outPressure:1 = false;
    char heatingCurrent:1 = false;
    char heatingVoltage:1 = false;
    char maxHeatingTime:1 = true;
    char maxCoolingTime:1 = true;
    char minHeatingTime:1 = false;
    char minCoolingTIme:1 = false;
    char flow:1 = false; //LPM
} TestMask;

typedef struct _TestParameters{
    int cycles = 1;
    float absorbTemp = 25;
    float releaseTemp = 80; //degreesC
    float inPressure = 8;      //psi?
    float outPressure = -8;
    float heatingCurrent = 0.8; //Amperes
    float heatingVoltage = 6; //Volts
    float maxHeatingTime = 3*60; //seconds
    float maxCoolingTime = 3*60;
    float minHeatingTime = 3*60;
    float minCoolingTIme = 3*60;
    float flow = 0.5; //LPM
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

public class Test{
    Test(TestMask TM, TestParameters setpoint, TestParameters
allowedVariance)
}



#endif
