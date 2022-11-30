#include <Arduino.h>
#include "config.h"
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
  sched.init(MCD);
 
  Task* smartLithing = new SmartLighting(PIN_LEDA, PIN_PIR, A0, LIGHT_THRESHOLD, SHUTDOWN_TIME);
  Task* waterLevelTask = new WaterLevelTask(new UltrasonicSensor(PIN_TRIGGER, PIN_ECHO));
  Task* waterTask = new WaterTask(PIN_LEDB, PIN_LEDC, PIN_SERVO, waterLevelTask);
  Task* lcdPrinting = new LcdTask();
  Task* blinking = new BlinkTask(PIN_LEDC);
  Task* serial = new SerialCommunication();
 
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), Button::isPressed, CHANGE);

  smartLithing->init(100);
  waterTask->init(100);
  blinking->init(500);
  lcdPrinting->init(500);
  waterLevelTask->init(500);
  serial->init(500);
  
  sched.addTask(serial);
  sched.addTask(smartLithing);
  sched.addTask(waterTask);
  sched.addTask(blinking);
  sched.addTask(lcdPrinting);
  sched.addTask(waterLevelTask);
}

void loop() {
  sched.schedule();
}