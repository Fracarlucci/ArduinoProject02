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
  motor.write(angle);  
}

int ServoMotor::readAngle() {
  return this->motor.read();
}

void ServoMotor::off() {
  motor.detach();
}