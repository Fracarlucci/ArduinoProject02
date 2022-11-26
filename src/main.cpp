#include <Arduino.h>

#include "scheduler/Scheduler.h"
#include "tasks/SmartLighting.h"
#include "tasks/WaterTask2.h"
#include "model/WaterState.h"
#include "tasks/BlinkTask.h"
#include "tasks/LcdTask.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(100);
 
  //Task* t0 = new SmartLighting(8, 9, A0, 3, 10);
  Task* w1 = new WaterState(new UltrasonicSensor(2, 3));
  Task* t1 = new WaterTask2(8, 11, 2, 3, 9, 13, A0);
  Task* lcdPrinting = new LcdTask();
  Task* blinking = new BlinkTask(11);
 
  //t0->init(100);
  t1->init(100);
  blinking->init(500);
  lcdPrinting->init(500);
  w1->init(100);
  
  //sched.addTask(t0);
  sched.addTask(t1);
  sched.addTask(blinking);
  sched.addTask(lcdPrinting);
  sched.addTask(w1);

}

void loop() {
  sched.schedule();
}