#ifndef SENSORS_H
#define SENSORS_H

#include "O2-Cycler.h"
#include <math.h>

class Sensors {
	static unsigned int *pP_Abs, *pP_Gauge, *pTherm, *pFlow, *pTFlow, *pO2, *pO2Therm, *pHeaterCurrent;
	const double THERM_A = 0.001129241;
	const double THERM_B = 0.0002341077;
	const double THERM_C = 0.00000008775468;
	const double C1 = -0.0361;
	const double C2 = 0.001896;
	const double C3 = -0.000004333;
	const double C0 = -(C3*pow(20, 3) + C2*pow(20, 1) + C1*20);
	float THERM_RESIST = 0.0;
	public:
	float valP_Abs, valP_Gauge, valTherm, valFlow, valTFlow, valO2, valO2Therm, valO2Comp, valHeaterCurrent = 0;
	Sensors (int);
	void getP_Abs();
	void printP_Abs();
	void getP_Gauge();
	void printP_Gauge();
	void getTherm();
	void printTherm();
	void getFlow();
	void printFlow();
	void getTFlow();
	void printTFlow();
	void getO2();
	void printO2();
	void getO2Therm();
	void printO2Therm();
	void getO2Comp();			//It is not required to get O2 and O2Therm vals separately before executing this function: it has all the functionality of the aformentioned functions
	void printO2Comp();
	void getHeaterCurrent();
	void printHeaterCurrent();
};


#endif
