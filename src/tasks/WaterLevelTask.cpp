#include "WaterLevelTask.h"

#include "../devices/Potentiometer.h"

WaterLevelTask::WaterLevelTask(const int pin_potentiometer, const int pin_LCD, const int pin_sonar) {

}

void WaterLevelTask::init(const int period) {
  Task::init(period);
  this->state = NORMAL;
}

void WaterLevelTask::tick() {
  switch (state)
  {
  case NORMAL:
    break;

    case PRE_ALARM:
  break;

    case ALARM:
  break;

    case MANUAL:
  break;
  
  default:
    break;
  }
}