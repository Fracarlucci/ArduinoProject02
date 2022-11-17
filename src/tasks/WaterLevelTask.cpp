#include "WaterLevelTask.h"

#include "../devices/Potentiometer.h"

WaterLevelTask::WaterLevelTask(const int pinLedB, const int pinLedC, const int pinPotentiometer, const int pinLCD, const int pinSonar) {
  blinkTask = new BlinkTask(pinLedC);
}

void WaterLevelTask::init(const int period, const int blinkPeriod) {
  Task::init(period);
  blinkTask->init(blinkPeriod);
  this->state = NORMAL;
}

void WaterLevelTask::tick() {
  switch (state)
  {
    case NORMAL:
      if(waterState->isNormal()){
        ledB->switchOn();
        ledC->switchOff();
        // sampling ogni PEN
      }else{
        state = PRE_ALARM;
      }
    break;

    case PRE_ALARM:
      if(currWaterLevel < W1){
        state = NORMAL;
      }
      else if(currWaterLevel > W2){
        state = ALARM;
      }
      else {
        blinkTask->tick();
        //sampling sonar
        //lcd->printText(currWaterLevel);
      }
    break;

    case ALARM:
    break;

    case MANUAL:
    break;
  
    default:
    break;
  }
}