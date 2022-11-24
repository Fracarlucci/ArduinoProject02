#include "BlinkTask.h"

BlinkTask::BlinkTask(int pin){
  this->pin = pin;    
}
  
void BlinkTask::init(int period){
  Task::init(period);
  led = new Led(pin); 
  ledState = OFF;    
}
  
void BlinkTask::tick(){
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

bool BlinkTask::updateAndCheckTime(int basePeriod){
  timeElapsed += basePeriod;
  if (timeElapsed >= myPeriod && state == PRE_ALARM){
    timeElapsed = 0;
    return true;
  } else {
    return false; 
  }
}