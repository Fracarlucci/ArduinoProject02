#ifndef __WATER_STATE__
#define __WATER_STATE__

#include "../tasks/Task.h"
#include "Arduino.h"
#include "../devices/UltrasonicSensor.h"

class WaterState: public Task {
    public: 
      WaterState(UltrasonicSensor* sensor);
      void init(int period);
	    void tick();

     private: 
      UltrasonicSensor* sensor;
};

#endif