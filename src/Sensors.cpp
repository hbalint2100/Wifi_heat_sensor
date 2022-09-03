#include "Sensors.h"

Sensors::Sensors() : dht22(digitalSensorPin,DHT22)
{
    if(digitalRead(isDigitalSensor)==HIGH)
    {
        humidityEnabled = true;
        dht22.begin();
        return;
    }
    humidityEnabled = false;
}

float Sensors::getHumidity()
{
    return dht22.readHumidity();
}

float Sensors::getTemperature()
{
    return dht22.readTemperature();
}

bool Sensors::isTemperatureEnabled()
{
    return true;
}

bool Sensors::isHumidityEnabled()
{
    return humidityEnabled;
}