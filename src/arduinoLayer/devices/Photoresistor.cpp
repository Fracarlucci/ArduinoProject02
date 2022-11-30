#include "Photoresistor.h"

Photoresistor::Photoresistor(const int photoresPin, const double lightThreshold){
  this->pin = photoresPin;
  this->THl = lightThreshold;
  pinMode(pin, INPUT);
}

double Photoresistor::readLuminosity() {
  return analogRead(pin);
}

bool Photoresistor::isLuminosityHigher(){
  return this->readLuminosity() > THl;
}