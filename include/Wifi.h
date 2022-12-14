#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "AdvancedString.h"
#include "LittleFS.h"

class Wifi
{
    private:
        String SSID;
        String PASSWD;
        bool findSubString(const String& text,String match,int& startPos);
        void wifiAPMode();
        void wifiSTAMode();
    public:
        Wifi(const String& ssid,const String& password);
        Wifi();
        static const int wifiStatusLed = 2;

        void getWifiData();
        void connect();
        bool disconnect();
        bool disable();
        bool enable();
        void setSSID(const String& SSID);
        void setPASSWD(const String& PASSWD);
    
};