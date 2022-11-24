#ifndef __BLINKTASK__
#define __BLINKTASK__

#include "Task.h"
#include "../devices/Led.h"
#include "WaterTask2.h"

extern State state;

class BlinkTask: public Task {
public:
  BlinkTask(int pin);  
  void init(int period);  
  void tick();
  bool updateAndCheckTime(int period);

private:
  int pin;
  Led* led;
  enum { ON, OFF} ledState;
};

#endif