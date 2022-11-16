#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__

#include "Arduino.h"

// define costant to get the luminosity
#define FREQ 5
#define PERIOD 1000/FREQ

class Photoresistor {

  public:
    Photoresistor(const int photoresPin, const double lightThreshold);
    double readLuminosity();
    bool isLuminosityHigher();

  private:
    int pin;
    double THl;

};

#endif  