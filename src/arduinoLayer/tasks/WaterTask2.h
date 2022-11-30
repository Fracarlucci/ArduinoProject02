#ifndef __WATER_TASK2__
#define __WATER_TASK2__

#include "Task.h"
#include "Arduino.h"
#include "SmartLighting.h"
#include "../devices/Led.h"
#include "../devices/UltrasonicSensor.h"
#include "../devices/LcdDisplay.h"
#include "../devices/ServoMotor.h"
#include "../model/WaterState.h"
#include "../devices/Button.h"
#include "../devices/Potentiometer.h"

#define W1 100
#define W2 50
#define PEA 500
#define PEP 1000
#define PEN 1500
#define WMAX 10

typedef enum {NORMAL, PRE_ALARM, ALARM, MANUAL} State;

extern float currDistance;
extern int valveAngle;
extern State state;
extern bool isPCControlled;
// extern LightingState lightingState;

class WaterTask2: public Task {
	public:
	WaterTask2(int pinLedB, int pinLedC, int pinTrigger, int pinEcho, int pinServoMotor/*, int pinButton, int pinPotentiometer*/, Task* sonar);
	void init(int period);
	void tick();
	static float getCurrDistance();

	private:
	Led* ledB;
	Led* ledC;
	UltrasonicSensor* sensor;
	LcdDisplay* lcd;
	ServoMotor* servoMotor;
	WaterState* waterState;
	Task* sonar;
	//Button* button;
	//Potentiometer* potentiometer;
};

#endif