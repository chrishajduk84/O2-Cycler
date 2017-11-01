#ifndef PID_H
#define PID_H

#include "O2-Cycler.h"
#include "Heater.h"

#define MAX_CONTROLLERS 15

template<class T> struct pointer_hack     { typedef T type; };
template<class T> struct pointer_hack<T*> { typedef T type; };
template<class T>
struct method_helper {
  typedef typename pointer_hack<T>::type Tx;
  typedef void (Tx::*type)(int);
};

template<class T> class PID;

typedef Heater PLACEHOLDER;
template<class T> struct ControllerItem { 
  PID<T>* controller;
  unsigned int updatePeriod;
  long lastTime;
  struct ControllerItem* next;
  bool initialized = false;
};

static unsigned long timer;
static struct ControllerItem<PLACEHOLDER>* controllerList;
extern unsigned int controllerCount;

template<class T> class PID{
    typename method_helper<T>::type updateFunction;
    T* updateObject;
    float* setSource;
    float* sensorSource;
    float K[5] = {1,1e-4,1,0,0};//Kp,Ki,Kd,lastError,Integral
    bool outputSet = false;
    
    public:
    PID(int updatePeriod){
      struct ControllerItem<T>* newNode;
      if (controllerCount == 0){
        controllerList = new ControllerItem<T>;
        newNode = controllerList;
      } else newNode = new ControllerItem<T>;
      
      struct ControllerItem<T>* tmp = controllerList;
      
      for (int i = 0; i < controllerCount; i++){
         tmp = tmp->next;
      }
      newNode->controller = this;
      newNode->updatePeriod = updatePeriod;
      newNode->lastTime = timer;
      tmp->next = newNode;
      
      newNode->initialized = true; //This should be the last thing running in the constructor!!
      Serial.println("NEWINSTANCE");
      controllerCount++;
      
    }
    ~PID(){
      struct ControllerItem<T>* tmp = controllerList;
      struct ControllerItem<T>* previous = tmp;
      for (int i = 0; i < controllerCount; i++){
        if (tmp->controller = this){
          previous->next = tmp->next;
          delete tmp;
          break;
        }
        previous = tmp;
        tmp = tmp->next;
      } 
    }
    void setSetpointSource(float* sourceData){setSource = sourceData;}
    void setSensorSource(float* sensorData){sensorSource = sensorData;}
    void setOutput(T* obj, typename method_helper<T>::type func){updateFunction = func; updateObject = obj;outputSet = true;}
    float* getSetpointSource(){return setSource;}
    float* getSensorSource(){return sensorSource;}
    int calculate(float set, float output, float* constants, int dt){
      float error = (set - output);
      constants[3] += error;
      float result = error*constants[0] + constants[3]*constants[1]; //Proportional and Integral term
      float derivative = 0;
      if (dt != 0){ //Derivative Term
        derivative = (error-constants[4])/dt*constants[2];
        result += derivative;
      }
      constants[4] = error;  

      //Prevent Overrun and integral wind-up
      if (result > 100){
        result = 100;
        constants[3] = (100 - error*constants[0] - derivative)/constants[1];
      }
      else if (result < 0){
        result = 0;
        constants[3] = (0 + error*constants[0] + derivative)/constants[1];
      }
      
      return (int)result;
    }
    void update(unsigned int dt){
      if (outputSet){
        int signal = calculate(*setSource,*sensorSource,K,dt);
        (updateObject->setPWM(signal));
      }
    }
};



#endif
