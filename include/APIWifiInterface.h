#pragma once
#include <Arduino.h>

class APIWifiInterface
{
    public:
    virtual const String& getSSID() = 0;
    virtual bool isConnected() = 0;
    virtual bool isDHCPEnabled() = 0;
    virtual String getStaticIP() = 0;
    virtual String getGatewayIP() = 0;
    virtual String getSubnetMask() = 0;
    virtual bool setSSID(const String& ssid) = 0;
    virtual bool setPASSWD(const String& passwd) = 0;
    virtual bool setStaticIP(const String& staticIP) = 0;
    virtual bool setGatewayIP(const String& gatewayIP) = 0;
    virtual bool setSubnetMask(const String& subnetMask) = 0;
    virtual bool loadConfig() = 0;
};