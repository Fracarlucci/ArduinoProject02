#include "Photoresistor.h"

double Photoresistor::readLuminosity() {

  int value = analogRead(PHOTORES_PIN);
  double valueInVolt = ((double) value) * 5/1024;
	return valueInVolt;

}

bool Photoresistor::isLuminosityHigher(){
 
  return this->readLuminosity() > THl;

}