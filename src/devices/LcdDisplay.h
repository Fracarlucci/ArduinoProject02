#ifndef __LCDDISPLAY__
#define __LCDDISPLAY__

#include <LiquidCrystal_I2C.h>
#include "Arduino.h"

class LcdDisplay {
    
    public:
        LcdDisplay();
        void setCursorDisplay(int x, int y);
        void printText(String text);

    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
};

#endif