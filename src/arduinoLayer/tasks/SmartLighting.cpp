#include "SmartLighting.h"
#include "../devices/Led.h"
#include "../devices/Pir.h"
#include "../devices/Photoresistor.h"

LightingState lightingState;

SmartLighting::SmartLighting(const int ledPin, const int pirPin, const int photoresPin, const int lightThreshold, const int shutdownTime){
  this->shutdownTime = shutdownTime;
  this->led = new Led(ledPin);   
  this->pir = new Pir(pirPin, 10);
  this->photores = new Photoresistor(photoresPin, lightThreshold);
}
  
void SmartLighting::init(const int period){
  Task::init(period);
  lightingState = OFF;
  this->elapsedTime = 0;
  this->shutdownTime *= 1000000;
}
  
void SmartLighting::tick(){
  Serial.println("LIGHT STATE: "+ String(lightingState));
  switch (lightingState){
    case OFF:
      if(this->pir->isDetected() && !this->photores->isLuminosityHigher()) {
        lightingState = ON;
      } else {
        this->led->switchOff();
      }
    break;
    case ON:
      if(this->photores->isLuminosityHigher()) {
        lightingState = OFF;
      } else if (!this->pir->isDetected()) {
        this->startTime = micros();
        lightingState = SHUTDOWN;
      } else {
        this->led->switchOn();
      }
    break;
    case SHUTDOWN:
      if(this->photores->isLuminosityHigher()) {
        lightingState = OFF;
      } else if(this->pir->isDetected()) {
        lightingState = ON;
      } else {
        this->elapsedTime = micros();
        if(this->elapsedTime - this->startTime >= this->shutdownTime) {
          lightingState = OFF;
        }
      }
    break;
  }
}