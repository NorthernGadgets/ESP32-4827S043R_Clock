#ifndef COMS_H
#define COMS_H

#include <WiFi.h>
#include <time.h>

class Coms {
public:
    Coms();
    bool connectWiFi();
    void setupTime();
    
private:
    const char* ssid = "NETWORK NAME";
    const char* password = "PASSWORD";
    const char* ntpServer = "pool.ntp.org";
    int gmtOffset_hour  = -5; // GMT offset in hours
    bool daylightSaving = true; // Daylight saving time enabled or disabled
    int gmtOffset_sec;
    int daylightOffset_sec;
};

#endif // COMS_H
