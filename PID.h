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

extern unsigned long int timer;

template<class T> class PID{
    typename method_helper<T>::type updateFunction;
    T* updateObject;
    float* setSource;
    float* sensorSource;
    float* K;//Kp,Ki,Kd,lastError,Integral
    bool outputSet = false;
    
    public:
    PID(){
      
    }
    ~PID(){}
    void setSetpointSource(float* sourceData){setSource = sourceData;}
    void setSensorSource(float* sensorData){sensorSource = sensorData;}
    void setOutput(T* obj, typename method_helper<T>::type func){updateFunction = func; updateObject = obj;outputSet = true;}
    void setGain(float* _K){
      //Must conform to Kp,Ki,Kd,lastError,Integral
      K = _K;
    }
    float* getSetpointSource(){return setSource;}
    float* getSensorSource(){return sensorSource;}
    int calculate(float set, float output, float* constants, int dt){
      float error = (set - output);
      //constants[3] += error;
      float result = error*constants[0] + constants[3]*constants[1]; //Proportional and Integral term
      float derivative = 0;
      /*if (dt != 0){ //Derivative Term
        derivative = (error-constants[4])/dt*constants[2];
        result += derivative;
      }
      constants[4] = error;  */

      //Prevent Overrun and integral wind-up
      if (result > 100){
        result = 100;
        //constants[3] = (100 - error*constants[0] - derivative)/constants[1];
      }
      else if (result < 0){
        result = 0;
        //constants[3] = (0 + error*constants[0] + derivative)/constants[1];
      }
      
      return (int)result;
    }
    void update(unsigned int dt){
      if (outputSet){
        int pidSignal = calculate(*setSource,*sensorSource,K,dt);
        (updateObject->setPWM(pidSignal));
      }
    }
};



#endif
