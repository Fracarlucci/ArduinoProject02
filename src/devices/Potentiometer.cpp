#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin) {
    pinMode(pin, INPUT);
}

int Potentiometer::getValue() {
    return analogRead(pin);
}