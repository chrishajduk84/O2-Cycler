#include "PID.h"

//Timer Interrupt -> PID -> Direct Control  

//Static Variables
//unsigned int mUpdatePeriod[MAX_CONTROLLERS];
//long timer = 0;
//PID* controllers[MAX_CONTROLLERS];

ISR(TIMER1_COMPA_vect)   // timer compare interrupt service routine
{
    for (int i = 0; i < MAX_CONTROLLERS; i++){
        if (controllers[i]){
            if (mUpdatePeriod[i] >= timer - controllers[i]->lastTime){
                controllers[i]->update(mUpdatePeriod[i]);
                controllers[i]->lastTime = timer;
            }
        }
    }
    timer += 1;
}

//Non-static
/*void (*PID::updateFunction)();
void* PID::setSource;
void* PID::sensorSource;
float* PID::K = {1,1,1,0,0};
int PID::mUpdatePeriod;
long PID::lastTime = 0;
*/
template<class T> PID<T>::PID(int updatePeriod){ //updatePeriod in milliseconds, keep above 100ms if possible
    //Register PID controller update with static interrupt
    
}

template<class T> PID<T>::~PID(){
    //Deregister PID Controller from static timer interrupt
    
}

template<class T> void PID<T>::setSetpointSource(void* data){ //Cannot be a function
    setSource = data;
}

template<class T> void PID<T>::setSensorSource(void* data){
    sensorSource = data;
}

/*PID::setSourceFunction(void* (*func)()){ //Must be a function
   FOR FUTURE USAGE 
}*/

template<class T> void PID<T>::setOutput(Heater* obj, void (Heater::*func)(int)){
   updateFunction = func; 
   updateObject = obj;
}

template<class T> void* PID<T>::getSetpointSource(){
  return setSource;
}

template<class T> void* PID<T>::getSensorSource(){
  return sensorSource;
}


//Calculate error and return response
//Kp = [0], Ki = [1], Kd = [2], sum = [3], lastValue = [4]
template<class T> int PID<T>::calculate(float setpoint, float output, float* K,int dt){
    float error = (output - setpoint);
    K[3] += error;
    float result = error*K[0] + K[3]*K[1] + (error-K[4])/dt*K[2];
    K[4] = error;    
    return result;
}

template<class T> void PID<T>::update(unsigned int dt){
  (updateObject->*updateFunction)(calculate(*(float*)setSource,*(float*)sensorSource,K,dt));
}

