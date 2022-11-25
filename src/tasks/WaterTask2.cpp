#include "WaterTask2.h"

float currDistance;
State state;
int valveAngle;

WaterTask2::WaterTask2(int pinLedB, int pinLedC, int pinTrigger, int pinEcho,
	int pinServoMotor, int pinButton, int pinPotentiometer) {
  this->ledB = new Led(pinLedB);
  this->ledC = new Led(pinLedC);
  this->sensor = new UltrasonicSensor(pinTrigger, pinEcho);
	this->servoMotor = new ServoMotor(pinServoMotor);
	this->button = new Button(pinButton);
	currDistance = 0;
}

void WaterTask2::init(int period) {
  Task::init(period);
	servoMotor->on();
  state = NORMAL;
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
					servoMotor->move(0);
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
					ledB->switchOff();
					ledC->switchOn();
					if(currDistance > WMAX) {
						valveAngle = map((long)currDistance, W2, WMAX, 0, 180);
						if(servoMotor->readAngle() != map((long)currDistance, W2, WMAX, 0, 180)){
							servoMotor->move(map((long)currDistance, W2, WMAX, 0, 180));
					}
				}
			}
		break;

		case MANUAL:
			Serial.println("MANUAL");
			if(button->isPressed()){
				state = ALARM;
			}
			else {
				valveAngle = map(val, 0, 1023, 0, 180);
				servoMotor->move(map(analogRead(A0), 0, 1023, 0, 180));
			}
		break;
	}
}