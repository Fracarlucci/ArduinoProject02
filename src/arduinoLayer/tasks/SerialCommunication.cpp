#include "SerialCommunication.h"
#include "Arduino.h"
#include "WaterTask.h"
#include "SmartLighting.h"

void SerialCommunication::init(int period) {
  Task::init(period);
  Serial.begin(9600);
  Serial.setTimeout(1);
}

void SerialCommunication::tick(){
  Serial.println("Bridge: "+ String(state));
  Serial.println("SmartLight: "+ String(lightingState));
  Serial.println("Graph: " + String(millis() /1000) + ", " + String(currDistance));
}