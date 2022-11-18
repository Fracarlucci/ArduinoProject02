#ifndef __WATER_LEVEL_TASK__
#define __WATER_LEVEL_TASK__

#include "Task.h"
#include "BlinkTask.h"
#include "../devices/Led.h"
#include "../devices/LcdDisplay.h"
#include "../devices/Potentiometer.h"
#include "../model/WaterState.h"

class WaterLevelTask: public Task{
public:
  WaterLevelTask(const int pinLedB, const int pinLedC, const int pinPotentiometer, const int pinLCD, const int pinTrigger, const int pinEcho);
  void init(const int period, const int blinkPeriod);
  void tick();
private:
  float currWaterLevel;
  Led* ledB;
  Led* ledC;
  LcdDisplay* lcd;
  WaterState* waterStateWorker;
  Potentiometer* potentiometer;

  const float W1 = 341;
  const float W2 = 682;
  const unsigned long int PEA = 60000;

  unsigned long int elapsedTime;
  //Lcd* lcd;
  BlinkTask* blinkTask;
  UltrasonicSensor* sensor;
  WaterState* waterState;
  enum{NORMAL, PRE_ALARM, ALARM, MANUAL} state;
};

#endif