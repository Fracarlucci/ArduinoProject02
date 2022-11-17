#ifndef __ULTRASONIC_SENSOR__
#define __ULTRASONIC_SENSOR__

class UltrasonicSensor {
    
    unsigned short triggerPin;
    unsigned short echoPin;
    
    public: 
        UltrasonicSensor(const unsigned short triggerPin, const unsigned short echoPin);
        float getDistance();

};

#endif