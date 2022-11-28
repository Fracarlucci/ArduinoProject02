#include "WaterState.h"
#include "../tasks/WaterTask2.h"
#include "../devices/UltrasonicSensor.h"
#include "Arduino.h"

WaterState::WaterState(UltrasonicSensor* sensor){
  this->sensor = sensor;
} 

// setting initial period
void WaterState::init(int period) {
  Task::init(period);
}

void WaterState::tick(){
  currDistance = this->sensor->getDistance();
}