# [Order an ESP32-4827S043R](https://s.click.aliexpress.com/e/_DB48igB "Order an ESP32-4827S043R")

## Clock Example

This repository includes a clock example that demonstrates how to use the ESP32-4827S043R to create a simple digital clock. This example utilizes the screen management functions to display the current time on the 4.3-inch display.

### Features

- Displays the current time in HH:MM format.
- Updates every second.
- Utilizes the touchscreen to demonstrate touch functionality.

### Setup

1. **Hardware Setup**:
   - Connect your ESP32-4827S043R module to your computer via USB.

2. **Required Libraries**:
   Ensure the following libraries are installed in your Arduino IDE:
   - **Arduino_GFX_Library** version 1.4.7
   - **XPT2046_Touchscreen** version 1.4
   - **Arduino ESP32 Boards** version 2.0.13

3. **Configure Wi-Fi and Time Settings**:
   - Open the `Coms.h` file and set your Wi-Fi and time details:
     ```cpp
     const char* ssid = "NETWORK NAME";
     const char* password = "PASSWORD";
     const char* ntpServer = "pool.ntp.org";
     int gmtOffset_hour  = -5; // GMT offset in hours
     bool daylightSaving = true; // Daylight saving time enabled or disabled
     ```

4. **Code Upload**:
   - Open the `4_3_0_Inch_Display_Fully_Working.ino` file in the Arduino IDE.
   - Select the correct board and port from the `Tools` menu.
   - Upload the code to the ESP32-4827S043R.

### Usage

Once the code is uploaded and the Wi-Fi and time settings are configured, the display will show the current time in HH:MM format. The time will update every second.

## About the ESP32-4827S043R

The ESP32-4827S043R is a versatile module that combines the powerful ESP32 microcontroller with a 4.3-inch display and resistive touch. This repository provides the base code to help you quickly get started with developing applications for this module.

## Features

**Screen Management**: Functions to initialize and control the 4.3-inch display.

**SD Card Handling**: Functions to interface with an SD card for data storage and retrieval.

## Required Libraries

- **Arduino_GFX_Library** version 1.4.7
- **XPT2046_Touchscreen** version 1.4
- **Arduino ESP32 Boards** version 2.0.13

## Specifications

- **Working voltage**: 4.75-5.25V
- **SPIFlash**: Default 32Mbit
- **RAM**: Internal 520KB
- **Wi-Fi**: 802.11b/g/n/e/i
- **Bluetooth**: Bluetooth 4.2 BR/EDR and BLE standard
- **Support interface**: (2Mbps) UART, SPI, I2C, PWM
- **Support TF card**: Maximum support 4G
- **IO ports**: 9
- **Serial port rate**: Default 115200bps
- **Spectrum range**: 2400 ~ 2483.5MHz
- **Antenna form**: Onboard PCB antenna, gain 2dBi
- **Image output format**: JPEG (only OV2640 support), BMP, GRAYSCALE
- **Packaging method**: DIP-16
- **Transmit power**:
  - 802.11b: 17±2dBm (@11Mbps)
  - 802.11g: 14±2dBm (@54Mbps)
  - 802.11n: 13±2dBm (@MCS7)
- **Receiving sensitivity**:
  - CCK, 1Mbps: -90dBm
  - CCK, 11Mbps: -85dBm
  - 6Mbps(1/2BPSK): -88dBm
  - 54Mbps (3/464-QAM): -70dBm
  - MCS7 (65Mbps, 72.2Mbps): -67dBm
- **Power consumption**:
  - Turn off the flash: 180mA@5V
  - Turn on the flash and adjust the brightness to the maximum: 310mA@5V
  - Deep-sleep: The lowest power consumption can reach 6mA@5V
  - Moderm-sleep: The lowest can reach 20mA@5V
  - Light-sleep: The lowest can reach 6.7mA@5V
- **Security**: WPA/WPA2/WPA2-Enterprise/WPS
- **Working temperature**: -20 ℃ ~ 70 ℃
- **Storage environment**: -40 ℃ ~ 125 ℃, <90%RH
