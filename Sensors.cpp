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
	csData.pAbs = (analogRead(*pP_Abs)-91.80193)/27.3;
  return csData.pAbs;
}

float Sensors::getP_Gauge(){
	csData.pGauge = ((analogRead(*pP_Gauge)/1023.0)-0.04)/(0.009/0.145038);
  return csData.pGauge;
}

float Sensors::getTherm(){
	csData.temperature = thermocouple.readCelsius();
  return csData.temperature;
}

float Sensors::getFlow(){
	csData.flow = (analogRead(*pFlow)-102)/410.0;
  return csData.flow;
}

float Sensors::getTFlow(){
	csData.tFlow = ((analogRead(*pTFlow)/204.6)-1.2)/0.96;
  return csData.tFlow;
}

float Sensors::getO2(){
	csData.O2 = (analogRead(*pO2)/(204.6*38.45*0.000585));
  return csData.O2;
}

float Sensors::getO2Therm(){
	//THERM_RESIST = 24900*((V3_3/(analogRead(*pO2Therm)/204.6))-1);
	csData.O2Temp = (1.0/(THERM_A + THERM_B*log(THERM_RESIST) + THERM_C*pow(log(THERM_RESIST), 3))) - 273.15;
  return csData.O2Temp;
}

float Sensors::getO2Comp(){
	float valO2 = getO2();
	float O2Therm = getO2Therm();
	csData.O2Comp = valO2 + C3*pow(O2Therm, 3) + C2*pow(O2Therm, 2) + C1*O2Therm + C0;
  return csData.O2Comp;
}

float Sensors::getHeaterCurrent(){
	csData.heaterCurrent = analogRead(*pHeaterCurrent)/(204.6*200*0.01);
  return csData.heaterCurrent;
}

CartridgeSensors* Sensors::getSensorData(){
  return &csData;
}

void Sensors::updateSensors(){
  getP_Abs();
  getP_Gauge();
  getTherm();
  getFlow();
  getTFlow();
  getO2Comp();;
  getHeaterCurrent();
}

