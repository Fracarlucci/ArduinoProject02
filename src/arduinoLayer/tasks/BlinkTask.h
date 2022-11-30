#ifndef __BLINKTASK__
#define __BLINKTASK__

#include "Task.h"
#include "WaterTask.h"
#include "../devices/Led.h"

class BlinkTask: public Task {
public:
  BlinkTask(int pin);
  void init(int period);
  void tick();

private:
  Led* led;
  enum { ON, OFF} ledState;
};

#endif