#include "WaterLevelTask.h"
#include "WaterTask2.h"
#include "../devices/UltrasonicSensor.h"
#include "Arduino.h"

WaterLevelTask::WaterLevelTask(UltrasonicSensor* sensor){
  this->sensor = sensor;
} 

// setting initial period
void WaterLevelTask::init(int period) {
  Task::init(period);
}

void WaterLevelTask::tick(){
  currDistance = this->sensor->getDistance();
}