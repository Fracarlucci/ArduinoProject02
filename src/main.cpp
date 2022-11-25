#include <Arduino.h>

#include "scheduler/Scheduler.h"
#include "tasks/SmartLighting.h"
#include "tasks/WaterTask2.h"
<<<<<<< HEAD
#include "model/WaterState.h"

=======
#include "tasks/BlinkTask.h"
#include "tasks/LcdTask.h"
>>>>>>> 13376c7b0447baddce2105568d2f6822e0096e43

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(100);
 
  //Task* t0 = new SmartLighting(8, 9, A0, 3, 10);
  WaterState* w1 = new WaterState(new UltrasonicSensor(2, 3));
  WaterTask2* t1 = new WaterTask2(8, 11, 2, 3, 9, 13, A0);
  LcdTask* lcdPrinting = new LcdTask();
  Task* blinking = new BlinkTask(11);
 
  //t0->init(100);
  t1->init(100);
  blinking->init(1000);
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