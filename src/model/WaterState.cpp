#include "WaterState.h"
#include "../devices/UltrasonicSensor.h"
#include "Arduino.h"

WaterState::WaterState(UltrasonicSensor* sensor, const float w1, const float w2){
  this->w1 = w1;
  this-> w2 = w2;
  this->sensor = sensor;
} 

float WaterState::getWaterLevel() {
    return this->sensor->getDistance();
}

float WaterState::getWaterLevelEveryMilliseconds(const unsigned long int startTime, const unsigned long int period) {
  if(millis() - startTime >= period) {
    return this->getWaterLevel();
  }
  return -1;
}
  
bool WaterState::isNormal(){
  return (this->sensor->getDistance() < w1);
}

bool WaterState::isPreAlarm(){
  return (this->sensor->getDistance() > w1 && this->sensor->getDistance() < w2);
}

bool WaterState::isAlarm(){
  return (this->sensor->getDistance() > w2);
}