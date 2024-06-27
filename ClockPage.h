#ifndef CLOCKPAGE_H
#define CLOCKPAGE_H

#include "Screen.h"
#include <time.h>

class ClockPage {
public:
    ClockPage(Screen *screen);
    void begin();
    void update();

private:
    Screen *screen;
    int prevHoursTens = -1;
    int prevHoursOnes = -1;
    int prevMinutesTens = -1;
    int prevMinutesOnes = -1;
    void drawDigit(int boxIndex, int digit);
    void clearBox(int boxIndex);
};

#endif // CLOCKPAGE_H
