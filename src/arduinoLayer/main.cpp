#include <Arduino.h>

#include "scheduler/Scheduler.h"
#include "tasks/SmartLighting.h"
#include "tasks/WaterTask2.h"
#include "model/WaterState.h"
#include "tasks/BlinkTask.h"
#include "tasks/LcdTask.h"
#include "devices/Button.h"
#include "tasks/SerialCommunication.h"

Scheduler sched;

void setup() {
  sched.init(10);
 
  Task* t0 = new SmartLighting(10, 6, A1, 3, 10);
  Task* w1 = new WaterState(new UltrasonicSensor(2, 3));
  Task* t1 = new WaterTask2(8, 11, 2, 3, 9/*, 13, A0*/, w1);
  Task* lcdPrinting = new LcdTask();
  Task* blinking = new BlinkTask(11);
  //Task* button = new ButtonTask(13);
  Task* serial = new SerialCommunication();
 
  attachInterrupt(0, Button::isPressed, CHANGE);

  t0->init(100);
  t1->init(100);
  blinking->init(500);
  lcdPrinting->init(500);
  w1->init(500);
  //button->init(50);
  serial->init(500);
  
  sched.addTask(t0);
  sched.addTask(t1);
  sched.addTask(blinking);
  sched.addTask(lcdPrinting);
  sched.addTask(w1);
  //sched.addTask(button);
  sched.addTask(serial);
}

void loop() {
  sched.schedule();
}