#include "SmartLighting.h"

#include "../devices/Led.h"
#include "../devices/Pir.h"
#include "../devices/Photoresistor.h"

SmartLighting::SmartLighting(const int ledPin, const int pirPin, const int photoresPin, const int lightThreshold, const int shutdownTime){
  this->shutdownTime = shutdownTime;
  this->led = new Led(ledPin);   
  this->pir = new Pir(pirPin, 10);
  this->photores = new Photoresistor(photoresPin, lightThreshold);
}
  
void SmartLighting::init(const int period){
  Task::init(period);
  this->state = OFF;
  this->elapsedTime = 0;
  this->shutdownTime *= 1000000;
}
  
void SmartLighting::tick(){
  switch (state){
    case OFF:
      this->led->switchOff();
      if(this->pir->isDetected() && !this->photores->isLuminosityHigher()) {
        this->state = ON;
      } 
    break;
    case ON:
      this->led->switchOn();
      if(this->photores->isLuminosityHigher()) {
        this->state = OFF;
      } else if (!this->pir->isDetected()) {
        this->startTime = micros();
        this->state = SHUTDOWN;
      }
    break;
    case SHUTDOWN:
      if(this->photores->isLuminosityHigher()) {
        this->state = OFF;
      } else if(this->pir->isDetected()) {
        this->state = ON;
      } else {
        this->elapsedTime = micros();
        if(this->elapsedTime - this->startTime >= this->shutdownTime) {
          this->state = OFF;
        }
      }
    break;
  }
}