#include "SensingTask.h"
#include "System.h"
#include "MQTTDataMessage.h"

long lastSent = 0;

void SensingTask::setup()
{
    setInterval(500);
}

void SensingTask::loop()
{
    int motion = System.getSensorCtrl().getMotion();
    String sensor = String(motion);
    Serial.println("Motion: "+sensor);
    if(motion&&(millis()-lastSent)>10000)
    {
        String topicMotion = "motion";
        MQTTDataMessage motionMessage(topicMotion,sensor,false);
        sendMessage<MQTTDataMessage>(motionMessage,"MQTT");
        Serial.println("Message sent");
        lastSent = millis();
    }
}