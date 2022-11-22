#include "WaterTask2.h"

WaterTask2::WaterTask2(int pinLedB, int pinLedC, int pinTrigger, int pinEcho, int pinServoMotor) {
  this->ledB = new Led(pinLedB);
  this->ledC = new Led(pinLedC);
  this->sensor = new UltrasonicSensor(pinTrigger, pinEcho);
	this->lcd = new LcdDisplay();
	this->servoMotor = new ServoMotor(pinServoMotor);

	this->blinkTask = new BlinkTask(pinLedC);
}

void WaterTask2::init(int period) {
  Task::init(period);
	//servoMotor->on();
  this->state = NORMAL;

	blinkTask->init(500);
}

void WaterTask2::tick() {
//lcd->clearDisplay();
lcd->setCursorDisplay(0, 0);
lcd->printText("Water level: " + String(sensor->getDistance()));
switch (state)
{
	case NORMAL:
			Serial.println("NORMAL");
			if(sensor->getDistance() < 150){
					state = PRE_ALARM;
			}
			else{
					ledB->switchOn();
					ledC->switchOff();
					/*if(servoMotor->readAngle() != 50){
						servoMotor->move(50);
					}*/
			}
	break;

	case PRE_ALARM:
			Serial.println("PRE_ALARM");
			if(sensor->getDistance() >= 150){
					state = NORMAL;
			}
			else if(sensor->getDistance() <= 10){
					state = ALARM;
			}
			else {
					ledB->switchOff();
					blinkTask->tick();
					//ledC->switchOn();
			}
	break;

	case ALARM:
			Serial.println("ALARM");
			if(sensor->getDistance() > 10){
				state = PRE_ALARM;
			}
			else {
				ledB->switchOff();
				ledC->switchOn();
				/*if(servoMotor->readAngle() != 100){
					servoMotor->move(100);
				}*/
			}
	break;
	}
}