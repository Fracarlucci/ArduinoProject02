#include "WaterTask2.h"

int valveAngle;
State state;
float currDistance = 0;
bool isPCControlled = false;

WaterTask2::WaterTask2(int pinLedB, int pinLedC, int pinServoMotor, Task* sonar) {
	this->ledB = new Led(pinLedB);
  this->ledC = new Led(pinLedC);
	this->servoMotor = new ServoMotor(pinServoMotor);
	this->sonar = sonar;
	currDistance = 0;
}

void WaterTask2::init(int period) {
  Task::init(period);
	servoMotor->on();
  state = NORMAL;
}

void WaterTask2::tick() {
	switch (state)
	{
		case NORMAL:
			Serial.println("NORMAL");
			if(currDistance < W1){
					state = PRE_ALARM;
			}
			else{
					sonar->setPeriod(PEN);
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
					sonar->setPeriod(PEP);
					ledB->switchOff();
			}
		break;

		case ALARM:
			Serial.println("ALARM");
			if(currDistance > W2){
				state = PRE_ALARM;
			}
			else {
				sonar->setPeriod(PEA);
				ledB->switchOff();
				ledC->switchOn();
				lightingState = OFF;
				if(currDistance > WMAX) {
					valveAngle = !isPCControlled ? map((long)currDistance, W2, WMAX, 0, 180) : valveAngle;
					isPCControlled = false;
					servoMotor->move(valveAngle);
				}
			}
		break;

		case MANUAL:
			Serial.println("MANUAL");
			lightingState = OFF;
			valveAngle = map(analogRead(A2), 0, 1023, 0, 180);
			servoMotor->move(valveAngle);
		break;
	}
}