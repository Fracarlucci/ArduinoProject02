#include "LcdTask.h"

extern State state;

void LcdTask::init(int period) {
  Task::init(period);
  lcd = new LcdDisplay();
}

void LcdTask::tick() {
  lcd->clearDisplay();
  lcd->setCursorDisplay(0, 0);
	lcd->printText("Water level: ");
  if(state == ALARM) {
    lcd->setCursorDisplay(0, 1);
    lcd->printText("Valve Angle: ");
  }
}