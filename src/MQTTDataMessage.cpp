#include "MQTTDataMessage.h"

bool MQTTDataMessage::isRetained()
{
    return retained;
}

MQTTDataMessage::MQTTDataMessage(){}

MQTTDataMessage::MQTTDataMessage(const String& i_topic,const String& i_payload,bool i_retained) : retained(i_retained), topic(i_topic), payload(i_payload){}

const String& MQTTDataMessage::getPayload()
{
    return payload;
}

const String& MQTTDataMessage::getTopic()
{
    return topic;
}