#include <Arduino.h>

#include "scheduler/Scheduler.h"
#include "tasks/SmartLighting.h"
#include "tasks/WaterTask.h"
#include "tasks/WaterLevelTask.h"
#include "tasks/BlinkTask.h"
#include "tasks/LcdTask.h"
#include "devices/Button.h"
#include "tasks/SerialCommunication.h"

Scheduler sched;

void setup() {
  sched.init(10);
 
  Task* t0 = new SmartLighting(9, 2, A1, 3, 10);
  Task* w1 = new WaterLevelTask(new UltrasonicSensor(8, 7));
  Task* t1 = new WaterTask(10, 11, 4, w1);
  Task* lcdPrinting = new LcdTask();
  Task* blinking = new BlinkTask(11);
  Task* serial = new SerialCommunication();
 
  attachInterrupt(digitalPinToInterrupt(3), Button::isPressed, CHANGE);

  t0->init(100);
  t1->init(100);
  blinking->init(500);
  lcdPrinting->init(500);
  w1->init(500);
  serial->init(500);
  
  sched.addTask(t0);
  sched.addTask(t1);
  sched.addTask(blinking);
  sched.addTask(lcdPrinting);
  sched.addTask(w1);
  sched.addTask(serial);
}

void loop() {
  sched.schedule();
}