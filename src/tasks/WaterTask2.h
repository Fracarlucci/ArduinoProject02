#ifndef __WATER_TASK2__
#define __WATER_TASK2__

#include "Task.h"
#include "Arduino.h"

#include "../devices/Led.h"
#include "../devices/UltrasonicSensor.h"
#include "../devices/LcdDisplay.h"
#include "../devices/ServoMotor.h"
#include "../devices/button.h"
#include "../devices/potentiometer.h"
//#include "blinkTask.h"

#define W1 100
#define W2 30
#define WMAX 10
typedef enum {NORMAL, PRE_ALARM, ALARM, MANUAL} State;

extern float currDistance;
extern int valveAngle;
extern State state;

class WaterTask2: public Task {
	public:
	WaterTask2(int pinLedB, int pinLedC, int pinTrigger, int pinEcho, int pinServoMotor, int pinButton, int pinPotentiometer);
	void init(int period);
	void tick();
	static float getCurrDistance();

	private:
	Led* ledB;
	Led* ledC;
	UltrasonicSensor* sensor;
	LcdDisplay* lcd;
	ServoMotor* servoMotor;
	Button* button;
	Potentiometer* potentiometer;

	//BlinkTask* blinkTask;
};

#endif