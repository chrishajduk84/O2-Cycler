#include "Sensors.h"
#include <Adafruit_MAX31855.h>
#include <SPI.h>
#include <math.h>

Sensors::Sensors(int sensorIndex){
	pP_Abs = (P_AbsPinout + sensorIndex);
	pP_Gauge = (P_GaugePinout + sensorIndex);
	pTherm = (ThermPinout + sensorIndex);
	pFlow = (FlowPinout + sensorIndex);
	pTFlow = &TFlowPinout;
	pO2 = &O2Pinout;
	pO2Therm = &O2ThermPinout;
	pHeaterCurrent = (HeaterCurrentPinout + sensorIndex);
	Adafruit_MAX31855 thermocouple(*pTherm);
}

void Sensors::getP_Abs(){
	valP_Abs = (analogRead(*pP_abs)-91.80193)/27.3;
}

void Sensors::getP_Gauge(){
	valP_Gauge = ((analogRead(*pP_Gauge)/1023.0)-0.04)/(0.009/0.145038);
}

void Sensors::getTherm(){
	valTherm = thermocouple.readCelsius();
}

void Sensors::getFlow(){
	valFlow = (analogRead(*pFlow)-102)/410.0;
}

void Sensors::getTFlow(){
	valTFlow = ((analogRead(*pTFlow)/204.6)-1.2)/0.96;
}

void Sensors::getO2(){
	valO2 = (analogRead(*pO2)/(204.6*38.45*0.000585));
}

void Sensors::getO2Therm(){
	THERM_RESIST = 24900*((V3_3/(analogRead(*pO2Therm)/204.6))-1);
	valO2Therm = (1.0/(THERM_A + THERM_B*log(THERM_RESIST) + THERM_C*pow(log(THERM_RESIST), 3))) - 273.15;
}

void Sensors::getO2Comp(){
	valO2 = (analogRead(*pO2)/(204.6*38.45*0.000585));
	THERM_RESIST = 24900*((V3_3/(analogRead(*pO2Therm)/204.6))-1);
	valO2Therm = (1.0/(THERM_A + THERM_B*log(THERM_RESIST) + THERM_C*pow(log(THERM_RESIST), 3))) - 273.15;
	valO2Comp = valO2 + C3*pow(valO2Therm, 3) + C2*pow(valO2Therm, 2) + C1*valO2Therm + C0;
}

void Sensors::getHeaterCurrent(){
	valHeaterCurrent = analogRead(*pHeaterCurrent)/(204.6*200*0.01);
}

