#include "Button.h"
#include "Arduino.h"

Button::Button(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);     
} 
  
static void Button::isPressed(){
  switch (state)
  {
    case ALARM:
        state = MANUAL;
    break;
  
    case MANUAL:
        state = ALARM;
    break;

    default:
    break;
  }
}
