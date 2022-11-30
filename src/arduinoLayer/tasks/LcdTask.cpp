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
  lcd->setCursorDisplay(0, 0);
	lcd->printText("Water level: " + String(currDistance));
  if(state == ALARM || state == MANUAL) {
    lcd->setCursorDisplay(0, 1);
    lcd->printText("Valve Angle: " + String(valveAngle));
  }
}