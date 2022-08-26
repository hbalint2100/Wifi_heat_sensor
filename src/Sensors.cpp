#include "Sensors.h"

const unsigned Sensors::digitalSensorPin = 13;

Sensors::Sensors() : dht22(digitalSensorPin,DHT22)
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