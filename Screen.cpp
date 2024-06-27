#include "Screen.h"

Screen::Screen(uint8_t touchCsPin, uint8_t touchIrqPin, SDCard *sdCard, Arduino_ESP32RGBPanel *bus)
    : ts(touchCsPin, touchIrqPin), sdCard(sdCard), touchCsPin(touchCsPin), touchIrqPin(touchIrqPin) {
    gfx = new Arduino_RPi_DPI_RGBPanel(
        bus,
        480 /* width */, 0 /* hsync_polarity */, 8 /* hsync_front_porch */, 4 /* hsync_pulse_width */, 43 /* hsync_back_porch */,
        272 /* height */, 0 /* vsync_polarity */, 8 /* vsync_front_porch */, 4 /* vsync_pulse_width */, 12 /* vsync_back_porch */,
        1 /* pclk_active_neg */, 9000000 /* prefer_speed */, true /* auto_flush */
    );

    // Initialize default box positions and dimensions (digital clock layout)
    int boxSize = 100;
    int colonWidth = 20;
    int colonHeight = 20;
    int spacing = 20;
    int startX = (gfx->width() - (2 * boxSize + colonWidth + spacing + 2 * boxSize + spacing)) / 2;
    int startY = (gfx->height() - boxSize) / 2;

    boxes[0] = {startX, startY, boxSize, boxSize};
    boxes[1] = {startX + boxSize + spacing, startY, boxSize, boxSize};
    colon[0] = {startX + 2 * boxSize + spacing + spacing / 2, startY + boxSize / 4 - colonHeight / 2, colonWidth, colonHeight};
    colon[1] = {startX + 2 * boxSize + spacing + spacing / 2, startY + 3 * boxSize / 4 - colonHeight / 2, colonWidth, colonHeight};
    boxes[2] = {startX + 2 * boxSize + colonWidth + 2 * spacing, startY, boxSize, boxSize};
    boxes[3] = {startX + 3 * boxSize + colonWidth + 3 * spacing, startY, boxSize, boxSize};
}

bool Screen::begin() {
    gfx->begin();
    gfx->fillScreen(BLUE);

    if (!ts.begin()) {
        return false;
    }

    ts.setRotation(0);

    if (!sdCard->begin()) {
        return false;
    }

    drawBoxes(); // Draw initial boxes

    return true;
}

void Screen::setRotation(uint8_t rotation) {
    ts.setRotation(rotation);
}

void Screen::drawTouchPoint() {
    if (ts.touched()) {
        TS_Point p = ts.getPoint();

        // Adjust touch coordinates to screen coordinates
        int16_t x = map(p.x, 200, 3800, gfx->width(), 0);  // Adjust these values if needed
        int16_t y = map(p.y, 200, 3800, 0, gfx->height()); // Adjust these values if needed

        // Ensure coordinates stay within bounds
        x = constrain(x, 0, gfx->width());
        y = constrain(y, 0, gfx->height());

        // Draw a circle at the touch point
        gfx->fillCircle(x, y, 5, RED);
    }
}

void Screen::drawBoxes() {
    for (int i = 0; i < 4; i++) {
        gfx->fillRoundRect(boxes[i].x, boxes[i].y, boxes[i].width, boxes[i].height, 10, WHITE);
    }
    // Draw the colon
    for (int i = 0; i < 2; i++) {
        gfx->fillRoundRect(colon[i].x, colon[i].y, colon[i].width, colon[i].height, 10, WHITE);
    }
}

void Screen::setBoxDimensions(int index, int x, int y, int width, int height) {
    if (index >= 0 && index < 4) {
        boxes[index] = {x, y, width, height};
    }
}

void Screen::setColonDimensions(int index, int x, int y, int width, int height) {
    if (index >= 0 && index < 2) {
        colon[index] = {x, y, width, height};
    }
}

void Screen::drawDigit(int boxIndex, int digit) {
    if (boxIndex >= 0 && boxIndex < 4) {
        char buffer[2];
        snprintf(buffer, sizeof(buffer), "%d", digit);
        gfx->setTextSize(8);
        gfx->setTextColor(BLACK);
        int16_t x1, y1;
        uint16_t w, h;
        gfx->getTextBounds(buffer, boxes[boxIndex].x, boxes[boxIndex].y, &x1, &y1, &w, &h);
        int16_t x = boxes[boxIndex].x + (boxes[boxIndex].width - w) / 2;
        int16_t y = boxes[boxIndex].y + (boxes[boxIndex].height - h) / 2;
        gfx->setCursor(x, y);
        gfx->print(buffer);
    }
}

void Screen::clearBox(int boxIndex) {
    if (boxIndex >= 0 && boxIndex < 4) {
        gfx->fillRoundRect(boxes[boxIndex].x, boxes[boxIndex].y, boxes[boxIndex].width, boxes[boxIndex].height, 10, WHITE);
    }
}
