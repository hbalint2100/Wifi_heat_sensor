#pragma once
#include "Message.h"
#include <Arduino.h>

class MQTTDataMessage : public Message
{
    private:
    bool retained;
    String topic;
    String payload;
    public:
    MQTTDataMessage();
    MQTTDataMessage(const String& topic,const String& payload,bool retained = true);
    bool isRetained();
    const String& getTopic();
    const String& getPayload();
};