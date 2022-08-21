#pragma once
#include "MQTT.h"
#include "LeanTask.h"
#include "MessengerInterface.h"
#include "ESP8266WiFi.h"
#include "MQTTDataMessage.h"

class MqttTask : public LeanTask, public MessengerInterface
{
    private:
    MQTT mqttCtrl;
    public:
    void setup();
    void loop();
};