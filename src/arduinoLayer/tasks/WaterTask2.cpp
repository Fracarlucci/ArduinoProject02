#include "WaterTask2.h"

int valveAngle;
State state;
float currDistance = 0;

WaterTask2::WaterTask2(int pinLedB, int pinLedC, int pinTrigger, int pinEcho, int pinServoMotor/*, int pinButton, int pinPotentiometer*/, Task* sonar) {
	this->ledB = new Led(pinLedB);
  this->ledC = new Led(pinLedC);
  this->sensor = new UltrasonicSensor(pinTrigger, pinEcho);
	this->servoMotor = new ServoMotor(pinServoMotor);
	//this->button = new Button(pinButton);
	this->waterState = new WaterState(this->sensor);
	this->sonar = sonar;
	currDistance = 0;
}

void WaterTask2::init(int period) {
  Task::init(period);
	servoMotor->on();
  state = NORMAL;
}

void WaterTask2::tick() {
	delay(15);
	//currDistance = sensor->getDistance();
	switch (state)
	{
		case NORMAL:
			//Serial.println("NORMAL");
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
			//Serial.println("PRE_ALARM");
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
			//Serial.println("ALARM");
			if(currDistance > W2){
				state = PRE_ALARM;
			}
			// else if(button->isPressed()){
			// 	state = MANUAL;
			// }
			else {
				sonar->setPeriod(PEA);
				ledB->switchOff();
				ledC->switchOn();
				lightingState = OFF;
				if(currDistance > WMAX) {
					valveAngle = map((long)currDistance, W2, WMAX, 0, 180);
					servoMotor->move(valveAngle);
				}
			}
		break;

		case MANUAL:
			//Serial.println("MANUAL");
			// if(button->isPressed()){
			// 	state = ALARM;
			// }
			//else {
			lightingState = OFF;
			valveAngle = map(analogRead(A0), 0, 1023, 0, 180);
			servoMotor->move(valveAngle);
			//}
		break;
	}
}