#ifndef __ULTRASONIC_SENSOR__
#define __ULTRASONIC_SENSOR__

class UltrasonicSensor {
    
    int triggerPin;
    int echoPin;
    
    public: 
        UltrasonicSensor(const int triggerPin, const int echoPin);
        float getDistance();

};

#endif