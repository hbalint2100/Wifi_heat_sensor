#pragma once
#include <Arduino.h>
#include "PubSubClient.h"
#include "WiFiClient.h"
#include "LittleFS.h"
#include "AdvancedString.h"

class MQTT
{
    private:
    WiFiClient wifiClient;
    PubSubClient mqttClient;
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
};