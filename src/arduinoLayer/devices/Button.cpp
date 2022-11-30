#include "Button.h"

unsigned long Button::startTime = micros();
unsigned long Button::elapsedTime = 0;
unsigned long Button::shutdownTime = 500000;
  
void Button::isPressed(){
  elapsedTime = micros();
  if((elapsedTime - startTime) >= shutdownTime){
    if(state == ALARM){
      state = MANUAL;
    }
    else if(state == MANUAL){
      state = ALARM;
    }
    startTime = micros();
  }   
}
