#pragma once
#include "DHT.h"
#define DHTTYPE DHT22

class Sensors
{
    private:
    DHT dht22;
    public:
    Sensors();
    float getHumidity();
    float getTemperature();

};