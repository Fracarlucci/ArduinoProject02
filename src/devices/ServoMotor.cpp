#include "ServoMotor.h"
#include "Arduino.h"

#define MAX_ANGLE 180
#define POT_VALUE 1023

ServoMotor::ServoMotor(const int pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void ServoMotor::on() {
  motor.attach(pin);
}

void ServoMotor::move(int angle) {
  // min is 544, max is 2400 (ref ServoTimer2.h)
  float coeff = (2400.0-544.0)/180;
  motor.write(544 + angle*coeff);  
}

int ServoMotor::readAngle() {
  return this->motor.read();
}

void ServoMotor::off() {
  motor.detach();
}