#include "Coms.h"

Coms::Coms() {}

bool Coms::connectWiFi() {
    WiFi.begin(ssid, password);
    int max_retries = 30; // Adjust the number of retries as needed
    while (WiFi.status() != WL_CONNECTED && max_retries > 0) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
        max_retries--;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi connected.");
        return true;
    } else {
        Serial.println("Failed to connect to WiFi.");
        return false;
    }
}

void Coms::setupTime() {
    gmtOffset_sec = gmtOffset_hour * 3600; // Convert hours to seconds
    daylightOffset_sec = daylightSaving ? 3600 : 0; // 1 hour in seconds if DST is enabled

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("Time synchronized with NTP server.");
}
