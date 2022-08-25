#include "SensingTask.h"
#include "System.h"
#include "MQTTDataMessage.h"

void SensingTask::setup()
{
    setInterval(90000L);
}

void SensingTask::loop()
{
    float temperature = 0;
    float humidity = 0;
    int i = 0;
    for(;i<10;i++)
    {
        temperature += System.getSensorCtrl().getTemperature();
        delay(3000L);
        humidity += System.getSensorCtrl().getHumidity();
        delay(3000L);
    }
    humidity = humidity/i;
    temperature = temperature/i;
    String topicTemp = "temperature";
    String topicHum = "humidity";
    String temp = String(temperature);
    String hum = String(humidity);
    MQTTDataMessage temperatureMessage(topicTemp,temp,true);
    MQTTDataMessage humidityMessage(topicHum,hum,true);
    sendMessage<MQTTDataMessage>(temperatureMessage,"MQTT");
    sendMessage<MQTTDataMessage>(humidityMessage,"MQTT");
    Serial.println("Message sent");
}