#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__

#include "Arduino.h"

// define the level of threshold
#define THl 10

// define costant to get the luminosity
#define PHOTORES_PIN A0
#define FREQ 5
#define PERIOD 1000/FREQ

class Photoresistor {

public:
  Photoresistor(const int photoresPin, const int lightThreshold);
  double readLuminosity();
  bool isLuminosityHigher();  
};

#endif  