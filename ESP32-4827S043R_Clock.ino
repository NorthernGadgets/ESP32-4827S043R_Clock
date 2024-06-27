#include <Arduino_GFX_Library.h>
#include <SPI.h>
#include <SD.h>
#include <WiFi.h>
#include <time.h>
#include "Screen.h"
#include "SDCard.h"
#include "Coms.h"
#include "ClockPage.h"

// Brightness control variable
int Brightness = 255; // Full brightness (range from 0 to 255)

// Initialize the display bus
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
    5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
    8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */
);

// Initialize the SDCard class
SDCard sdCard(10); // Hardcoded SD card CS pin

// Initialize the screen class
Screen screen(38, 18, &sdCard, bus);

// Initialize the Coms class
Coms coms;

// Initialize the ClockPage class
ClockPage clockPage(&screen);

void setup(void) {
    Serial.begin(115200); // Start serial communication for debugging

    // Set up TFT backlight pin
    pinMode(2, OUTPUT);
    analogWrite(2, Brightness);

    // Initialize the screen
    if (!screen.begin()) {
        Serial.println("Failed to initialize screen");
        while (1);
    }

    Serial.println("Screen initialized.");

    // List files on SD card
    sdCard.listFiles("/", screen.gfx);

    // Connect to WiFi
    if (!coms.connectWiFi()) {
        Serial.println("Failed to connect to WiFi");
        while (1);
    }

    // Setup time using NTP
    coms.setupTime();

    // Initialize the clock page
    clockPage.begin();
}

void loop(void) {
    // Update and display the current time
    clockPage.update();
    screen.drawTouchPoint();
    delay(25); // Refresh every second
}
