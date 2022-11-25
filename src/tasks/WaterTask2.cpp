#include "WaterTask2.h"

float currDistance;
State state;
int valveAngle;

WaterTask2::WaterTask2(int pinLedB, int pinLedC, int pinTrigger, int pinEcho,
	int pinServoMotor, int pinButton, int pinPotentiometer) {
  this->ledB = new Led(pinLedB);
  this->ledC = new Led(pinLedC);
  this->sensor = new UltrasonicSensor(pinTrigger, pinEcho);
	this->lcd = new LcdDisplay();
	this->servoMotor = new ServoMotor(pinServoMotor);
	this->button = new Button(pinButton);
	this->potentiometer = new Potentiometer(pinPotentiometer);
	currDistance = 0;

	//this->blinkTask = new BlinkTask(pinLedC);
}

void WaterTask2::init(int period) {
  Task::init(period);
	servoMotor->on();
  state = NORMAL;

	//blinkTask->init(500);
}

void WaterTask2::tick() {
	delay(15);
	currDistance = sensor->getDistance();

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
			else if(button->isPressed()){
				state = MANUAL;
			}
			else {
				valveAngle = map((long)currDistance, W2, WMAX, 544, 2400);
				ledB->switchOff();
				ledC->switchOn();
				if(servoMotor->readAngle() != valveAngle){
					servoMotor->move(map((long)currDistance, W2, WMAX, 0, 180));
					delay(15);
				}
			}
		break;

		case MANUAL:
			Serial.println("MANUAL");
			if(button->isPressed()){
				state = ALARM;
			}
			else {
				//potentiometer->getValue();
				servoMotor->move(map((long)potentiometer->getValue(), 0, 1023, 0, 180));
			}
		break;
	}
}