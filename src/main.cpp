#include <Arduino.h>

#include "scheduler/Scheduler.h"
#include "tasks/SmartLighting.h"
#include "tasks/WaterTask2.h"
#include "model/WaterState.h"
#include "tasks/BlinkTask.h"
#include "tasks/LcdTask.h"
#include "tasks/ButtonTask.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(10);
 
  //Task* t0 = new SmartLighting(8, 9, A0, 3, 10);
  Task* w1 = new WaterState(new UltrasonicSensor(2, 3));
  Task* t1 = new WaterTask2(10, 8, 11, 2, 3, 9/*, 13, A0*/);
  Task* lcdPrinting = new LcdTask();
  Task* blinking = new BlinkTask(11);
  Task* button = new ButtonTask(13);
 
  //t0->init(100);
  t1->init(100);
  blinking->init(500);
  lcdPrinting->init(500);
  w1->init(500);
  button->init(50);
  
  //sched.addTask(t0);
  sched.addTask(t1);
  sched.addTask(blinking);
  sched.addTask(lcdPrinting);
  sched.addTask(w1);
  sched.addTask(button);
}

void loop() {
  sched.schedule();
}