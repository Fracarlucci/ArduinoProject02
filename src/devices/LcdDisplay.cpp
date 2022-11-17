#include "LcdDisplay.h"

LcdDisplay::LcdDisplay() {
    lcd.init();
    lcd.backlight();
} 

void LcdDisplay::printText(String text) {
    lcd.print(text);
}

void LcdDisplay::setCursorDisplay(int x, int y) {
    lcd.setCursor(x, y);
}

