#include "MqttTask.h"
#include "System.h"
#include "MQTTDataMessage.h"

void MqttTask::setup()
{
    if(!System.getMqttCtrl().isSet())
    {
        disable();
        return;
    }
    if(WiFi.status()==WL_CONNECTED)
    {
        System.getMqttCtrl().connect();
        setInterval(20000L);
    }
    else
    {
        setInterval(40000L);
    }
    Serial.println("MQTT task started");
}

void MqttTask::loop()
{
    if(WiFi.status()==WL_CONNECTED)
    {
        if(!System.getMqttCtrl().getClient().loop())
        {
            System.getMqttCtrl().connect();
        }
        if(System.getMqttCtrl().getClient().connected())
        {
            MQTTDataMessage buffer[5];
            if(receiveMessage<MQTTDataMessage>(buffer,5,"MQTT"))
            {
                for(int i = 0; i < 5; i++)
                {
                    if(!buffer[i].getTopic().isEmpty()&&!buffer[i].getTopic().isEmpty())
                    {
                        System.getMqttCtrl().getClient().publish(buffer[i].getTopic().c_str(),buffer[i].getPayload().c_str(),buffer[i].isRetained());
                    }
                }
            }
        }
        if(getInterval()==40000L)
        {
            setInterval(20000L);
        }
    }
}