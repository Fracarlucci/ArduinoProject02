#ifndef __WATER_LEVEL_TASK__
#define __WATER_LEVEL_TASK__

#include "Task.h"
#include "BlinkTask.h"
#include "../devices/Led.h"
#include "../devices/LcdDisplay.h"
#include "../devices/Potentiometer.h"
#include "../devices/Button.h"
#include "../devices/ServoMotor.h"
#include "../model/WaterState.h"

#define PEN 60000
#define PEP 60000
#define PEA 60000

class WaterLevelTask: public Task{
public:
  WaterLevelTask(const int pinLedB, const int pinLedC, const int pinPotentiometer,
    const int pinLCD, const int pinTrigger, const int pinEcho, const int buttonPin, const int pinServoMotor);
  void init(const int period, const int blinkPeriod);
  void tick();
private:
  float currWaterLevel;
  Led* ledB;
  Led* ledC;
  LcdDisplay* lcd;
  WaterState* waterStateWorker;
  Potentiometer* potentiometer;
  Button* button;
  ServoMotor* servoMotor;

  const float W1 = 341;
  const float W2 = 682;

  unsigned long int elapsedTime;

  BlinkTask* blinkTask;
  UltrasonicSensor* sensor;
  WaterState* waterState;
  enum{NORMAL, PRE_ALARM, ALARM, MANUAL} state;
};

#endif