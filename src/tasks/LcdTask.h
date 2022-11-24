#ifndef __LCDTASK__
#define __LCDTASK__

#include "Task.h"
#include "../devices/LcdDisplay.h"
#include "WaterTask2.h"

extern State state;

class LcdTask: public Task {
public:
  void init(int period);  
  void tick();

private:
  LcdDisplay* lcd;
};

#endif