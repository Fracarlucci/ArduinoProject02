#ifndef __WATER_STATE__
#define __WATER_STATE__

#include "../devices/UltrasonicSensor.h"

class WaterState {
    
    UltrasonicSensor* sensor;

    float w1;
    float w2;

    public: 
        WaterState(UltrasonicSensor* sensor, const float w1, const float w2);
        float getWaterLevel();
        float getWaterLevelEveryMilliseconds(const unsigned long int startTime, const unsigned long int period);
        bool isNormal();
        bool isPreAlarm();
        bool isAlarm();

};

#endif