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


template<class T> class PID{
    typename method_helper<T>::type updateFunction;
    T* updateObject;
    void* setSource;
    void* sensorSource;
    float* K;
    
    public:
    PID(int updatePeriod){};
    ~PID(){};
    void setSetpointSource(void* data){setSource = data;}
    void setSensorSource(void* data){sensorSource = data;}
    void setOutput(T* obj, typename method_helper<T>::type func){updateFunction = func; updateObject = obj;} //TODO:TEMPORARY
    void* getSetpointSource(){return setSource;}
    void* getSensorSource(){return sensorSource;}
    int calculate(float setpoint, float output, float* K, int dt){
      float error = (output - setpoint);
      K[3] += error;
      float result = error*K[0] + K[3]*K[1] + (error-K[4])/dt*K[2];
      K[4] = error;    
      return result;
    }
    void update(unsigned int dt){(updateObject->*updateFunction)(calculate(*(float*)setSource,*(float*)sensorSource,K,dt));}
};

typedef Heater PLACEHOLDER;
typedef struct _ControllerItem { 
  PID<PLACEHOLDER>* controller;
  unsigned int updatePeriod;
  long lastTime;
  struct _ControllerItem* next;
} ControllerItem;

static unsigned long timer;
static ControllerItem* controllerList;



#endif
