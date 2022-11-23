#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

#include "ServoTimer2.h"

class ServoMotor {
public:
  ServoMotor(const int pin);
  void on();
  void move(int angle);
  int readAngle();
  void off();

private:
  int pin;
  ServoTimer2 motor;
};

#endif