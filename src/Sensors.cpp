#include "Sensors.h"

Sensors::Sensors() : dht22(13,DHT22)
{
    dht22.begin();
}

float Sensors::getHumidity()
{
    return dht22.readHumidity();
}

float Sensors::getTemperature()
{
    return dht22.readTemperature();
}