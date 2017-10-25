#ifndef O2_CYCLER_H
#define O2_CYCLER_H

#define NUM_CARTRIDGES 3

#include <Arduino.h>

static unsigned int heaterPinout[NUM_CARTRIDGES] = {31,33,35};
static unsigned int vAPinout[NUM_CARTRIDGES] = {1,2,3};
static unsigned int vBPinout[NUM_CARTRIDGES] = {1,2,3};
static unsigned int vCPinout[NUM_CARTRIDGES] = {1,2,3};
static unsigned int pAPinout[NUM_CARTRIDGES] = {1,2,3};
static unsigned int pBPinout[NUM_CARTRIDGES] = {1,2,3};

#endif
