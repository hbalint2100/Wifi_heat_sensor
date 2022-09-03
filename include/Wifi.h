#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "AdvancedString.h"
#include "LittleFS.h"
#include "APIWifiInterface.h"

class Wifi : public APIWifiInterface
{
    private:
        String SSID;
        String PASSWD;
        IPAddress staticIP;
        IPAddress gateway;
        IPAddress subnetMask;
        bool disabled;
        bool findSubString(const String& text,String match,int& startPos);
        void wifiAPMode();
        bool wifiSTAMode();
        bool forcedApMode();
    public:
        Wifi(const String& ssid,const String& password);
        Wifi();
        static const unsigned wifiStatusLed = 2;
        static const unsigned forcedApModePin = 12;

        const String& getSSID();
        const String& getPASSWD();
        void getWifiData();
        void connect();
        bool disconnect();
        bool disable();
        bool enable();
        bool setSSID(const String& SSID);
        bool setPASSWD(const String& PASSWD);

        bool isConnected();
        bool isDHCPEnabled();
        String getStaticIP();
        String getGatewayIP();
        String getSubnetMask();
        bool setStaticIP(const String& staticIP);
        bool setGatewayIP(const String& gatewayIP);
        bool setSubnetMask(const String& subnetMask);
        bool loadConfig();
    
};