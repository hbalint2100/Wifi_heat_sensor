#pragma once
#include "DHT.h"
#define DHTTYPE DHT22

class Sensors
{
    private:
    DHT dht22;
    static const unsigned digitalSensorPin;
    public:
    Sensors();
    float getHumidity();
    float getTemperature();

};