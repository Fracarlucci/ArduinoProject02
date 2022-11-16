#include "Photoresistor.h"

Photoresistor::Photoresistor(const int photoresPin, const double lightThreshold){
  this->pin = photoresPin;
  this->THl = lightThreshold;
  pinMode(pin, INPUT);
}

double Photoresistor::readLuminosity() {
  int value = analogRead(pin);
  double valueInVolt = ((double) value) * 5/1024;
	return valueInVolt;
}

bool Photoresistor::isLuminosityHigher(){
  return this->readLuminosity() > THl;
}