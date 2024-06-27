#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino_GFX_Library.h>
#include "SDCard.h"
#include <XPT2046_Touchscreen.h>

class Screen {
public:
    Screen(uint8_t touchCsPin, uint8_t touchIrqPin, SDCard *sdCard, Arduino_ESP32RGBPanel *bus);
    bool begin();
    void drawTouchPoint();
    void setRotation(uint8_t rotation);
    void drawBoxes();
    void setBoxDimensions(int index, int x, int y, int width, int height);
    void setColonDimensions(int index, int x, int y, int width, int height);
    void drawDigit(int boxIndex, int digit);
    void clearBox(int boxIndex);

    // Make gfx public for accessibility
    Arduino_RPi_DPI_RGBPanel *gfx;

private:
    XPT2046_Touchscreen ts;
    SDCard *sdCard; // Pointer to SDCard class
    uint8_t touchCsPin;
    uint8_t touchIrqPin;
    struct Box {
        int x;
        int y;
        int width;
        int height;
    } boxes[4];
    Box colon[2];
};

#endif // SCREEN_H
