#include "PID.h"


//Timer Interrupt -> PID -> Direct Control  

//Static Variables
//unsigned int mUpdatePeriod[MAX_CONTROLLERS];
//long timer = 0;
//PID* controllers[MAX_CONTROLLERS];
unsigned int controllerCount;

ISR(TIMER1_COMPA_vect)   // timer compare interrupt service routine
{
    //unsigned int a[3]= {0,0,0};
    struct ControllerItem<Heater>* list = controllerList;
    for (int i = 0; i < controllerCount; i++){
//      if (list->initialized){
//          if (list->updatePeriod <= (timer - list->lastTime)){
//                list->controller->update(list->updatePeriod);
//                list->lastTime = timer;
//                //a[i] = 2;
//          }
//          else {
//            //a[i] = 1;
//          }
//      
//      }
      list = list->next;
      //Serial.println(i);
    }
    timer += 1;
    //char buf[50];
    //sprintf(buf,"%u,%u,%u, %u",(unsigned int)a[0],(unsigned int)a[1],(unsigned int)a[2], controllerCount);
    //Serial.println(buf);
    //Serial.println(controllerCount);
}

//Non-static
/*void (*PID::updateFunction)();
void* PID::setSource;
void* PID::sensorSource;
float* PID::K = {1,1,1,0,0};
int PID::mUpdatePeriod;
long PID::lastTime = 0;
*/
/*template <typename T> PID<T>::PID(int updatePeriod){ //updatePeriod in milliseconds, keep above 100ms if possible
    //Register PID controller update with static interrupt
    
}

template <typename T> PID<T>::~PID(){
    //Deregister PID Controller from static timer interrupt
    
}

template <typename T> void PID<T>::setSetpointSource(void* data){ //Cannot be a function
    setSource = data;
}

template <typename T> void PID<T>::setSensorSource(void* data){
    sensorSource = data;
}

/*PID::setSourceFunction(void* (*func)()){ //Must be a function
   FOR FUTURE USAGE 
}

template <typename T> void PID<T>::setOutput(Heater* obj, void (Heater::*func)(int)){
   updateFunction = func; 
   updateObject = obj;
}

template <typename T> void* PID<T>::getSetpointSource(){
  return setSource;
}

template <typename T> void* PID<T>::getSensorSource(){
  return sensorSource;
}


//Calculate error and return response
//Kp = [0], Ki = [1], Kd = [2], sum = [3], lastValue = [4]
template <typename T> int PID<T>::calculate(float setpoint, float output, float* K,int dt){
    float error = (output - setpoint);
    K[3] += error;
    float result = error*K[0] + K[3]*K[1] + (error-K[4])/dt*K[2];
    K[4] = error;    
    return result;
}

template <typename T> void PID<T>::update(unsigned int dt){
  (updateObject->*updateFunction)(calculate(*(float*)setSource,*(float*)sensorSource,K,dt));
}*/

