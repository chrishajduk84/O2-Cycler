#ifndef PID_H
#define PID_H

#include "O2-Cycler.h"
#include "Heater.h"

#define MAX_CONTROLLERS 15

/*template<class T> struct pointer_hack     { typedef T type; };
template<class T> struct pointer_hack<T*> { typedef T type; };
template<class T>
struct method_helper {
  typedef typename pointer_hack<T>::type Tx;
  typedef bool (Tx::*type)(Tx const&) const;
};*/



template<class T> class PID{
    void (Heater::*updateFunction)(int);
    Heater* updateObject;
    void* setSource;
    void* sensorSource;
    float* K;
    
    public:
    long lastTime;
    PID(int updatePeriod);
    ~PID();
    void setSetpointSource(void* data);
    void setSensorSource(void* data);
    //void setOutput(void (method_helper<T>::*func)(int));
    void setOutput(Heater* obj, void (Heater::*func)(int)); //TODO:TEMPORARY
    void* getSetpointSource();
    void* getSensorSource();
    int calculate(float setpoint, float output, float* K, int dt);
    void update(unsigned int dt);
};

static unsigned int mUpdatePeriod[MAX_CONTROLLERS];
static unsigned long timer;
static PID<void*>* controllers[MAX_CONTROLLERS]; 

template class PID<Heater>;

#endif
