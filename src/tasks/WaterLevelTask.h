#ifndef __WATER_LEVEL_TASK__
#define __WATER_LEVEL_TASK__

#include "Task.h"

#include "../devices/Potentiometer.h"

class WaterLevelTask: public Task{
public:
  WaterLevelTask(const int pin_potentiometer, const int pin_LCD, const int pin_sonar);
  void init(const int period);
  void tick();
private:
  enum{NORMAL, PRE_ALARM, ALARM, MANUAL} state;
};

#endif