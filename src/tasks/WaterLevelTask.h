#ifndef __WATER_LEVEL_TASK__
#define __WATER_LEVEL_TASK__

#include "Task.h"
#include "BlinkTask.h"
#include "../devices/Led.h"

#define W1 341
#define W2 682

class WaterLevelTask: public Task{
public:
  WaterLevelTask(const int pinLedB, const int pinLedC, const int pinPotentiometer, const int pinLCD, const int pinSonar);
  void init(const int period, const int blinkPeriod);
  void tick();
private:
  float currWaterLevel;
  Led* ledB;
  Led* ledC;
  //Lcd* lcd;
  BlinkTask* blinkTask;
  enum{NORMAL, PRE_ALARM, ALARM, MANUAL} state;
};

#endif