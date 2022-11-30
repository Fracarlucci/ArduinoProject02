#include "WaterTask.h"

//global vars for lcd and serial communications
int valveAngle;
State state;	// it is used from all classes 
float currDistance = 0;
bool isPCControlled = false;

WaterTask::WaterTask(int pinLedB, int pinLedC, int pinServoMotor, Task* sonar) {
	this->ledB = new Led(pinLedB);
  this->ledC = new Led(pinLedC);
	this->servoMotor = new ServoMotor(pinServoMotor);
	this->sonar = sonar;
	currDistance = 0;
}

void WaterTask::init(int period) {
  Task::init(period);
	servoMotor->on();
  state = NORMAL;
}

//it manage the movement of the servo and leds
void WaterTask::tick() {
	switch (state)
	{
		case NORMAL:
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
			if(currDistance >= W1){
					state = NORMAL;
			}
			else if(currDistance <= W2){
					state = ALARM;
			}
			else {
					sonar->setPeriod(PEP);
					ledB->switchOn();
			}
		break;

		case ALARM:
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
			lightingState = OFF;
			valveAngle = map(analogRead(A1), 0, 1023, 0, 180);
			servoMotor->move(valveAngle);
		break;
	}
}