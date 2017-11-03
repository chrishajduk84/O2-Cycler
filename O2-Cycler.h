#ifndef O2_CYCLER_H
#define O2_CYCLER_H

#define NUM_CARTRIDGES 3

#include <Arduino.h>

static unsigned int heaterPinout[NUM_CARTRIDGES] = {31,33,35};
static unsigned int vAPinout[NUM_CARTRIDGES] = {11,10,9}; // Inlet 2-way
static unsigned int vBPinout[NUM_CARTRIDGES] = {7,5,3}; // Outlet 2-way
static unsigned int vCPinout[NUM_CARTRIDGES] = {6,4,46}; // Outlet 3-way
//static unsigned int vAPinout[NUM_CARTRIDGES] = {1,2,3};
//static unsigned int vBPinout[NUM_CARTRIDGES] = {1,2,3};
//static unsigned int vCPinout[NUM_CARTRIDGES] = {1,2,3};
static unsigned int pAPinout[NUM_CARTRIDGES] = {24,26,22};
static unsigned int pBPinout[NUM_CARTRIDGES] = {49,47,45};
static unsigned int P_AbsPinout[NUM_CARTRIDGES] = {9,8,7};
static unsigned int P_GaugePinout[NUM_CARTRIDGES] = {10,11,12};
static unsigned int ThermPinout[NUM_CARTRIDGES] = {38,40,42};
static unsigned int FlowPinout[NUM_CARTRIDGES] = {6,5,4};
static unsigned int TFlowPinout = 0;
static unsigned int O2Pinout = 3;
static unsigned int O2ThermPinout = 2;
static unsigned int HeaterCurrentPinout[NUM_CARTRIDGES] = {15,14,13};

unsigned long int myMillis();

#endif
