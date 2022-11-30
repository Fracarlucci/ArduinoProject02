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
  Serial.println("Bridge: "+ String(state));
  Serial.println("SmartLight: "+ String(lightingState));
  Serial.println("Graph: " + String(millis()) + ", " + String(currDistance));

  //Slider Input
  String inputData = Serial.readString();
  if(inputData.startsWith("Slider:")) {
    valveAngle = inputData.substring(inputData.lastIndexOf(":") + 1, inputData.length()).toInt();
    isPCControlled = true;
  }
}