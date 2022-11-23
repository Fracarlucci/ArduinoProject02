#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

#include <Adafruit_TiCoServo.h>

class ServoMotor {
public:
  ServoMotor(const int pin);
  void on();
  void move(int value);
  int readAngle();
  void off();

private:
  int pin;
  Adafruit_TiCoServo motor;
};

#endif