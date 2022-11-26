#include "BlinkTask.h"

BlinkTask::BlinkTask(int pin){
  this->led = new Led(pin); 
}
  
void BlinkTask::init(int period){
  Task::init(period);
  ledState = OFF;    
}
  
void BlinkTask::tick(){
  if(state == PRE_ALARM){
    switch (ledState){
      case OFF:
        led->switchOn();
        ledState = ON; 
      break;
      
      case ON:
        led->switchOff();
        ledState = OFF;
      break;
    }
  }
}
