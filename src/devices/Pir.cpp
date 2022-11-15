#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pin, int calibrating_time) {
    this->pin = pin;
    this->calibrating_time = calibrating_time;
    pinMode(pin, INPUT);
    this->calibrating();
}

void Pir::calibrating() {
    Serial.print("Calibrating sensor... ");
    for(int i = 0; i < this->calibrating_time; i++) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" done");
    Serial.println("PIR SENSOR READY.");
    this->detected_status = false;
}

bool Pir::isDetected() {
    int current = digitalRead(this->pin);
    if (current != this->detected_status) {
        this->detected_status = current;
    }
}