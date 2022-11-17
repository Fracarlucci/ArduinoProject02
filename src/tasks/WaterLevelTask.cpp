#include "WaterLevelTask.h"

#include "../devices/Potentiometer.h"
#include "../devices/LcdDisplay.h";

WaterLevelTask::WaterLevelTask(const int pinLedB, const int pinLedC, const int pinPotentiometer, const int pinLCD, const int pinTrigger, const int pinEcho) {
  blinkTask = new BlinkTask(pinLedC);
  this->waterStateWorker = new WaterState(new UltrasonicSensor(pinTrigger, pinEcho), this->W1, this->W2);
  this->lcd = new LcdDisplay();
  this->potentiometer = new Potentiometer(pinPotentiometer);
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
      const float waterLevel = this->waterStateWorker->getWaterLevelEveryMilliseconds(this->elapsedTime, this->PEA);
      if(waterLevel != -1) {
        this->lcd->printText("Livello Acqua: ");
        this->lcd->printText("Apertura Valvola: ");
        this->elapsedTime = millis();
      }
    break;
  
    default:
    break;
  }
}