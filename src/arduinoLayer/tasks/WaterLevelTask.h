#ifndef __WATER_STATE__
#define __WATER_STATE__

#include "Task.h"
#include "Arduino.h"
#include "../devices/UltrasonicSensor.h"

class WaterLevelTask: public Task {
    public: 
      WaterLevelTask(UltrasonicSensor* sensor);
      void init(int period);
	    void tick();

     private: 
      UltrasonicSensor* sensor;
};

#endif