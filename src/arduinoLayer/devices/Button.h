#ifndef __BUTTON__
#define __BUTTON__

#include "../tasks/WaterTask2.h"

class Button {
public: 
  Button(int pin);
  static void isPressed();

private:
  int pin;
};

#endif