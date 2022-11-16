#include <Arduino.h>
#include "./tasks/BlinkTask.h"

#define LED_PIN 8

BlinkTask blinkTask(LED_PIN);

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    blinkTask.init(1000);
}

void loop() {
  blinkTask.tick();
  delay(1000);
}