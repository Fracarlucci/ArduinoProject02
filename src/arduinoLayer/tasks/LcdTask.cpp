#include "LcdTask.h"
#include "WaterTask.h"

void LcdTask::init(int period) {
  Task::init(period);
  lcd = new LcdDisplay();
}

void LcdTask::tick() {
  lcd->clearDisplay();
  if(state == NORMAL) {
    return;
  }
  if(state == PRE_ALARM) {
    lcd->setCursorDisplay(0, 0);
    lcd->printText("Water level: " + String(currDistance));
    lcd->setCursorDisplay(0, 2);
    lcd->printText("State: PRE ALARM");
  }
  if(state == ALARM || state == MANUAL) {
    lcd->setCursorDisplay(0, 1);
    lcd->printText("Valve Angle: " + String(valveAngle));
      lcd->setCursorDisplay(0, 2);
  lcd->printText("State: ALARM");
  }
}