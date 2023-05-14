#pragma once
#include "DHT.h"
#include "APISensorInterface.h"
#define DHTTYPE DHT22

class Sensors : public APISensorInterface
{
    private:
    //DHT dht22;
    static const unsigned digitalSensorPin = 13;
    static const unsigned isDigitalSensor = 14;
    static const unsigned motionSensorPin = D7;
    bool humidityEnabled;
    int motionAvg[20];
    int motionIndex;
    int motionSensitivity;
    public:
    Sensors();
    float getHumidity();
    float getTemperature();
    bool isTemperatureEnabled();
    bool isHumidityEnabled();
    bool isMotionEnabled();
    int getMotion();
    int getMotionSensitivity();
    void setMotionSensitivity(int motionSensitivity);
};