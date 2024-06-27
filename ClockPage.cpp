#include "ClockPage.h"

ClockPage::ClockPage(Screen *screen) : screen(screen) {}

void ClockPage::begin() {
    // Draw initial boxes
    screen->setBoxDimensions(0, 15, 25, 100, 100);
    screen->setBoxDimensions(1, 120, 25, 100, 100);
    screen->setBoxDimensions(2, 260, 25, 100, 100);
    screen->setBoxDimensions(3, 365, 25, 100, 100);
    screen->setColonDimensions(0, 230, 40, 20, 20); // Upper part of the colon
    screen->setColonDimensions(1, 230, 90, 20, 20); // Lower part of the colon
    screen->drawBoxes();
}

void ClockPage::update() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }
    int hours = timeinfo.tm_hour % 12;
    if (hours == 0) {
        hours = 12;
    }
    int minutes = timeinfo.tm_min;

    int hoursTens = (hours < 10) ? -1 : hours / 10;
    int hoursOnes = hours % 10;
    int minutesTens = minutes / 10;
    int minutesOnes = minutes % 10;

    // Update hours tens place if it has changed
    if (hoursTens != prevHoursTens) {
        clearBox(0);
        if (hoursTens != -1) {
            drawDigit(0, hoursTens);
        }
        prevHoursTens = hoursTens;
    }

    // Update hours ones place if it has changed
    if (hoursOnes != prevHoursOnes) {
        clearBox(1);
        drawDigit(1, hoursOnes);
        prevHoursOnes = hoursOnes;
    }

    // Update minutes tens place if it has changed
    if (minutesTens != prevMinutesTens) {
        clearBox(2);
        drawDigit(2, minutesTens);
        prevMinutesTens = minutesTens;
    }

    // Update minutes ones place if it has changed
    if (minutesOnes != prevMinutesOnes) {
        clearBox(3);
        drawDigit(3, minutesOnes);
        prevMinutesOnes = minutesOnes;
    }
}

void ClockPage::drawDigit(int boxIndex, int digit) {
    screen->drawDigit(boxIndex, digit);
}

void ClockPage::clearBox(int boxIndex) {
    screen->clearBox(boxIndex);
}
