#include "WaterTask2.h"

State state;

WaterTask2::WaterTask2(int pinLedB, int pinLedC, int pinTrigger, int pinEcho, int pinServoMotor) {
  this->ledB = new Led(pinLedB);
  this->ledC = new Led(pinLedC);
  this->sensor = new UltrasonicSensor(pinTrigger, pinEcho);
	this->lcd = new LcdDisplay();
	this->servoMotor = new ServoMotor(pinServoMotor);
	this->currDistance = 0;
	//this->blinkTask = new BlinkTask(pinLedC);
}

void WaterTask2::init(int period) {
  Task::init(period);
	servoMotor->on();
  state = NORMAL;

	//blinkTask->init(500);
}

void WaterTask2::tick() {
	//lcd->clearDisplay();
	delay(15);
	currDistance = sensor->getDistance();
	lcd->setCursorDisplay(0, 0);
	lcd->printText("Water level: " + String(currDistance));

	switch (state)
	{
		case NORMAL:
			Serial.println("NORMAL");
			if(currDistance < W1){
					state = PRE_ALARM;
			}
			else{
					ledB->switchOn();
					ledC->switchOff();
					//if(servoMotor->readAngle() != 544){
						servoMotor->move(0);
					//	delay(15);
					//}
			}
		break;

		case PRE_ALARM:
			Serial.println("PRE_ALARM");
			if(currDistance >= W1){
					state = NORMAL;
			}
			else if(currDistance <= W2){
					state = ALARM;
			}
			else {
					ledB->switchOff();
					//blinkTask->tick();
					//ledC->switchOn();
			}
		break;

		case ALARM:
			Serial.println("ALARM");
			if(currDistance > W2){
				state = PRE_ALARM;
			}
			else {
				ledB->switchOff();
				ledC->switchOn();
				if(servoMotor->readAngle() != map((long)currDistance, W2, WMAX, 544, 2400)){
					servoMotor->move(map((long)currDistance, W2, WMAX, 0, 180));
					delay(15);
				}
				lcd->setCursorDisplay(0,1);
				lcd->printText("Valve angle: " + String(map(servoMotor->readAngle(), 544, 2400, 0, 180)));
			}
		break;
	}
}