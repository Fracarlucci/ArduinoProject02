#include "LcdTask.h"
#include "WaterTask2.h"

void LcdTask::init(int period) {
  Task::init(period);
  lcd = new LcdDisplay();
}

void LcdTask::tick() {
  if(state == NORMAL) {
    return;
  }
  lcd->clearDisplay();
  lcd->setCursorDisplay(0, 0);
	lcd->printText("Water level: " + String(currDistance));
  if(state == ALARM) {
    lcd->setCursorDisplay(0, 1);
    lcd->printText("Valve Angle: " + String(valveAngle));
  }
}