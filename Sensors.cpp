#include "Sensors.h"
#include <SPI.h>

Sensors::Sensors(int sensorIndex):thermocouple(*pTherm){
	pP_Abs = (P_AbsPinout + sensorIndex);
	pP_Gauge = (P_GaugePinout + sensorIndex);
	pTherm = (ThermPinout + sensorIndex);
	pFlow = (FlowPinout + sensorIndex);
	pTFlow = &TFlowPinout;
	pO2 = &O2Pinout;
	pO2Therm = &O2ThermPinout;
	pHeaterCurrent = (HeaterCurrentPinout + sensorIndex);
}

float Sensors::getP_Abs(){
	valP_Abs = (analogRead(*pP_Abs)-91.80193)/27.3;
  return valP_Abs;
}

float Sensors::getP_Gauge(){
	valP_Gauge = ((analogRead(*pP_Gauge)/1023.0)-0.04)/(0.009/0.145038);
  return valP_Gauge;
}

float Sensors::getTherm(){
	valTherm = thermocouple.readCelsius();
  return valTherm;
}

float Sensors::getFlow(){
	valFlow = (analogRead(*pFlow)-102)/410.0;
  return valFlow;
}

float Sensors::getTFlow(){
	valTFlow = ((analogRead(*pTFlow)/204.6)-1.2)/0.96;
  return valTFlow;
}

float Sensors::getO2(){
	valO2 = (analogRead(*pO2)/(204.6*38.45*0.000585));
  return valO2;
}

float Sensors::getO2Therm(){
	//THERM_RESIST = 24900*((V3_3/(analogRead(*pO2Therm)/204.6))-1);
	valO2Therm = (1.0/(THERM_A + THERM_B*log(THERM_RESIST) + THERM_C*pow(log(THERM_RESIST), 3))) - 273.15;
  return valO2Therm;
}

float Sensors::getO2Comp(){
	valO2 = (analogRead(*pO2)/(204.6*38.45*0.000585));
	float O2Therm = getO2Therm();
	valO2Comp = valO2 + C3*pow(O2Therm, 3) + C2*pow(O2Therm, 2) + C1*O2Therm + C0;
  return valO2Comp;
}

float Sensors::getHeaterCurrent(){
	valHeaterCurrent = analogRead(*pHeaterCurrent)/(204.6*200*0.01);
  return valHeaterCurrent;
}

