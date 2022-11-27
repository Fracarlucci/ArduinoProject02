#ifndef __BUTTONTASK__
#define __bUTTONTASK__

#include "Task.h"
#include "WaterTask2.h"
#include "../devices/Button.h"

class ButtonTask: public Task {
public:
  ButtonTask(int pin);
  void init(int period);
  void tick();

private:
  Button* button;
};

#endif