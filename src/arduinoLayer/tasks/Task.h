#ifndef __TASK__
#define __TASK__

#include "Arduino.h"

class Task {
public:
  virtual void init(int period){
    this->myPeriod = period;  
    timeElapsed = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= this->myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }

  void setPeriod(int period) {
    this->myPeriod = period;
  }

protected:
  int myPeriod;
  int timeElapsed;
};

#endif
