#include <Arduino.h>

#include "scheduler/Scheduler.h"
#include "tasks/SmartLighting.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(100);
 
  Task* t0 = new SmartLighting(1, 1, 1, 1, 1);
  t0->init(100);
  
  sched.addTask(t0);
}

void loop() {
  sched.schedule();
}