#include "UltrasonicSensor.h"
#include "Arduino.h"

UltrasonicSensor::UltrasonicSensor(const unsigned short triggerPin, const unsigned short echoPin){
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
  pinMode(this->triggerPin, OUTPUT);
  pinMode(this->echoPin, INPUT);     
} 
  
float UltrasonicSensor::getDistance(){
  digitalWrite(this->triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->triggerPin, LOW);
  return pulseIn(this->echoPin, HIGH) * 0.034 / 2; 
}
