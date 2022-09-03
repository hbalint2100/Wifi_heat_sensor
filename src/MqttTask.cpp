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
                Serial.println("Message received");
                int trying = 0;
                int success = 0;
                for(int i = 0; i < 5; i++)
                {
                    if(!buffer[i].getTopic().isEmpty()&&!buffer[i].getTopic().isEmpty())
                    {
                        trying++;
                        if(System.getMqttCtrl().getClient().publish(
                            (System.getMqttCtrl().getRoute()+buffer[i].getTopic()).c_str(),
                            buffer[i].getPayload().c_str(),buffer[i].isRetained()))
                        {
                            success++;
                        }
                    }
                }
                if(success == trying)
                {
                    Message message;
                    message.setMessageText("All data successfully sent");
                    sendMessage<Message>(message,"System");
                }
            }
        }
        if(getInterval()==40000L)
        {
            setInterval(20000L);
        }
    }
}