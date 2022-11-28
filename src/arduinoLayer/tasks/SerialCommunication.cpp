#include "SerialCommunication.h"
#include "Arduino.h"
#include "WaterTask2.h"
#include "SmartLighting.h"

void SerialCommunication::init(int period) {
  Task::init(period);
  Serial.begin(9600);
  Serial.setTimeout(1);
}

void SerialCommunication::tick(){
  Serial.println("l" + String(lightingState));
  Serial.println("s" + String(state));
}