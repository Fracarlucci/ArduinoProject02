#include <Arduino.h>

#include "scheduler/Scheduler.h"
#include "tasks/SmartLighting.h"
#include "tasks/WaterLevelTask.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(100);
 
  //Task* t0 = new SmartLighting(8, 9, A0, 3, 10);
  WaterLevelTask* t1 = new WaterLevelTask(1, 0, 99, 100, 2, 3, 88, 11);
 
  //t0->init(100);
  t1->init(100, 500);
  
  //sched.addTask(t0);
  sched.addTask(t1);
}

void loop() {
  sched.schedule();
}