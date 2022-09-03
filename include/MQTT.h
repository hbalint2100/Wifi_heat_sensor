#pragma once
#include <Arduino.h>
#include "PubSubClient.h"
#include "WiFiClient.h"
#include "LittleFS.h"
#include "AdvancedString.h"
#include "APIMqttInterface.h"

class MQTT : public APIMqttInterface
{
    private:
    WiFiClient wifiClient;
    PubSubClient mqttClient;
    String brokerIP;
    unsigned brokerPort;
    String deviceName;
    String username;
    String password;
    bool set;
    public:
    MQTT();
    ~MQTT();
    bool connect();
    bool isSet();
    String getRoute();
    const String& getDeviceName();
    void getMqttData();
    PubSubClient& getClient();
    const String& getBrokerIP();
    const String& getUsername();
    unsigned getBrokerPort();
    bool setUsername(const String& username);
    bool setPassword(const String& password);
    bool setDeviceName(const String& deviceName);
    bool setBrokerIP(const String& brokerIP);
    bool setBrokerPort(unsigned port);
    bool loadConfig();
};