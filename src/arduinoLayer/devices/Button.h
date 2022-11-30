#ifndef __BUTTON__
#define __BUTTON__

#include "../tasks/WaterTask.h"

class Button {
public: 
  static void isPressed();

private:
  static unsigned long startTime;
  static unsigned long elapsedTime;
  static unsigned long shutdownTime;
};

#endif