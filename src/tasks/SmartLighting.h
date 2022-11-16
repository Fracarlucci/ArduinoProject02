#ifndef __SMART_LIGHTING_TASK__
#define __SMART_LIGHTING_TASK__

#include "Task.h"

#include "../devices/Led.h"
#include "../devices/Photoresistor.h"
#include "../devices/Pir.h"

class SmartLighting: public Task {

  Led* led;
  Pir* pir;
  Photoresistor* photores;

  int shutdownTime;
  int lightThreshold;

  enum { ON, OFF, SHUTDOWN} state;

public:

  SmartLighting(const int ledPin, const int pirPin, const int photoresPin, const int shutdownTime, const int lightThreshold);  
  void init(const int period);  
  void tick();
};

#endif
