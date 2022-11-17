#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

#include "Servo.h"

class ServoMotor {
public:
  ServoMotor(const int pin);
  void on();
  void move(int value);
  void off();

private:
  int pin;
  Servo motor;
};

#endif