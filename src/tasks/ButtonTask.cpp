#include "ButtonTask.h"

ButtonTask::ButtonTask(int pin){
  this->button = new Button(pin); 
}

void ButtonTask::init(int period){
  Task::init(period);
}

void ButtonTask::tick(){
  switch (state)
  {
    case ALARM:
      if(button->isPressed()){
        state = MANUAL;
      }
    break;
  
    case MANUAL:
      if(button->isPressed()){
        state = ALARM;
      }
    break;

    default:
    break;
  }
}