#pragma once
#include <Arduino.h>

class APIMqttInterface
{
    public:
    virtual const String& getBrokerIP() = 0;
    virtual unsigned getBrokerPort() = 0;
    virtual const String& getUsername() = 0;
    virtual const String& getDeviceName() = 0;
    virtual bool setUsername(const String& username) = 0;
    virtual bool setPassword(const String& password) = 0;
    virtual bool setDeviceName(const String& deviceName) = 0;
    virtual bool setBrokerIP(const String& brokerIP) = 0;
    virtual bool setBrokerPort(unsigned port) = 0;
    virtual bool loadConfig() = 0;
};