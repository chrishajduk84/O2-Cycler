#ifndef SENSORS_H
#define SENSORS_H

#include "O2-Cycler.h"
#include <math.h>
#include <Adafruit_MAX31855.h>

typedef struct _cartridgeSensors{
  float pAbs;
  float pGauge;
  float temperature;
  float flow;
  float tFlow;
  float O2;
  float O2Temp;
  float O2Comp;
  float heaterCurrent;
} CartridgeSensors;

class Sensors {
	unsigned int *pP_Abs, *pP_Gauge, *pTherm, *pFlow, *pTFlow, *pO2, *pO2Therm, *pHeaterCurrent;
  const float N = 10.0;
	const double THERM_A = 0.001129241;
	const double THERM_B = 0.0002341077;
	const double THERM_C = 0.00000008775468;
	const double C1 = -0.0361;
	const double C2 = 0.001896;
	const double C3 = -0.000004333;
	const double C0 = -(C3*pow(20, 3) + C2*pow(20, 1) + C1*20);
	float THERM_RESIST = 0.0;
  float valO2;
  float O2Therm;  
  Adafruit_MAX31855* thermocouple;
  CartridgeSensors csData;
  
	public:
  
	Sensors (int sensorIndex);
  ~Sensors();

	float getP_Abs();
	void printP_Abs();
	float getP_Gauge();
	void printP_Gauge();
	float getTherm();
	void printTherm();
	float getFlow();
	void printFlow();
	float getTFlow();
	void printTFlow();
	float getO2();
	void printO2();
	float getO2Therm();
	void printO2Therm();
	float getO2Comp();			//It is not required to get O2 and O2Therm vals separately before executing this function: it has all the functionality of the aformentioned functions
	void printO2Comp();
	float getHeaterCurrent();
	void printHeaterCurrent();
  CartridgeSensors* getSensorData();
  void updateSensors();
};


#endif
