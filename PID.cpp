#include "PID.h"

unsigned int controllerCount;

ISR(TIMER1_COMPA_vect)   // timer compare interrupt service routine
{
//    struct ControllerItem<Heater>* list = controllerList;
//    for (int i = 0; i < controllerCount; i++){
//      if (list->initialized){
//          if (list->updatePeriod <= (timer - list->lastTime)){
//                list->controller->update(list->updatePeriod);
//                list->lastTime = timer;
//          }
//          else {
//          }
//      
//      }
//      list = list->next;
      //Serial.println(i);
//    }
    timer += 1;
}

