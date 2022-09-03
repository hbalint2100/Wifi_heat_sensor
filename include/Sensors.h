#pragma once
#include "DHT.h"
#include "APISensorInterface.h"
#define DHTTYPE DHT22

class Sensors : public APISensorInterface
{
    private:
    DHT dht22;
    static const unsigned digitalSensorPin = 13;
    static const unsigned isDigitalSensor = 14;
    bool humidityEnabled;
    public:
    Sensors();
    float getHumidity();
    float getTemperature();
    bool isTemperatureEnabled();
    bool isHumidityEnabled();
};