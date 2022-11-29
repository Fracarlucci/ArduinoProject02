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
        //mando nella seriale lo stato 
				Serial.println("Bridge: "+ String(state));
    break;
  
    case MANUAL:
        state = ALARM;
        //mando nella seriale lo stato 
				Serial.println("Bridge: "+ String(state));
    break;

    default:
    break;
  }
}
