#ifndef __BLINKTASK__
#define __BLINKTASK__

#include "Task.h"
#include "../devices/Led.h"

class BlinkTask: public Task {
public:
  BlinkTask(int pin);  
  void init(int period);  
  void tick();

private:
  int pin;
  Led* led;
  enum { ON, OFF} state;
};

#endif