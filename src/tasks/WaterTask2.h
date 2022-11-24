#ifndef __WATER_TASK2__
#define __WATER_TASK2__

#include "Task.h"
#include "Arduino.h"

#include "../devices/Led.h"
#include "../devices/UltrasonicSensor.h"
#include "../devices/LcdDisplay.h"
#include "../devices/ServoMotor.h"
#include "blinkTask.h"

#define W1 100
#define W2 50
#define WMAX 10
typedef enum {NORMAL, PRE_ALARM, ALARM, MANUAL} State;

class WaterTask2: public Task {
	public:
	WaterTask2(int pinLedB, int pinLedC, int pinTrigger, int pinEcho, int pinServoMotor);
	void init(int period);
	void tick();

	private:
	float currDistance;
	Led* ledB;
	Led* ledC;
	UltrasonicSensor* sensor;
	LcdDisplay* lcd;
	ServoMotor* servoMotor;

	BlinkTask* blinkTask;
};

#endif