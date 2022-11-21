#include "WaterLevelTask.h"

#include "../devices/Potentiometer.h"
#include "../devices/LcdDisplay.h"
#include "../devices/Button.h"

WaterLevelTask::WaterLevelTask(const int pinLedB, const int pinLedC, const int pinPotentiometer, const int pinLCD, const int pinTrigger, const int pinEcho, const int buttonPin) {
  this->blinkTask = new BlinkTask(pinLedC);
  this->waterState = new WaterState(new UltrasonicSensor(pinTrigger, pinEcho), this->W1, this->W2);
  this->lcd = new LcdDisplay();
  this->potentiometer = new Potentiometer(pinPotentiometer);
  this->button = new Button(buttonPin);
  this->elapsedTime = 0;
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
        lcd->setCursorDisplay(0, 0);
        currWaterLevel = waterState->getWaterLevelEveryMilliseconds(elapsedTime, PEn);
        if(currWaterLevel != -1){
          lcd->printText("WL: " + String(currWaterLevel));
          elapsedTime = millis();
        }
      }else{
        state = PRE_ALARM;
      }
    break;

    case PRE_ALARM:
      if(waterState->isNormal()){
        state = NORMAL;
      }
      else if(waterState->isAlarm()){
        state = ALARM;
      }
      else {
        blinkTask->tick();
        lcd->setCursorDisplay(0, 0);
        currWaterLevel = waterState->getWaterLevelEveryMilliseconds(elapsedTime, PEA);
        if(currWaterLevel != -1){
          lcd->printText("Water level: " + String(currWaterLevel));
          elapsedTime = millis();
        }     
      }
    break;

    case ALARM:

    break;

    case MANUAL:
      const float waterLevel = this->waterStateWorker->getWaterLevelEveryMilliseconds(this->elapsedTime, this->PEA);
      if(waterLevel != -1) {
        this->lcd->setCursorDisplay(0, 0);
        this->lcd->printText("WL: " + String(waterLevel) + " Pot: " + String(this->servoMotor->readAngle()));
        this->elapsedTime = millis();
      }
      if(this->button->isPressed()) {
        state = ALARM;
      } else {
        this->servoMotor->move(map(this->potentiometer->getValue(), 0, 1023, 0, 180));
      }
    break;
  
    default:
    break;
  }
}