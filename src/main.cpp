#include <Arduino.h>

#include "scheduler/Scheduler.h"
#include "tasks/SmartLighting.h"
#include "tasks/WaterTask2.h"
#include "tasks/BlinkTask.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(100);
 
  //Task* t0 = new SmartLighting(8, 9, A0, 3, 10);
  WaterTask2* t1 = new WaterTask2(8, 11, 2, 3, 9);
  BlinkTask* blinking = new BlinkTask(11);
 
  //t0->init(100);
  t1->init(100);
  blinking->init(1000);
  
  //sched.addTask(t0);
  sched.addTask(t1);
  sched.addTask(blinking);
}

void loop() {
  sched.schedule();
}