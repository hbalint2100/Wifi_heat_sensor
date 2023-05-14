#include "Sensors.h"

Sensors::Sensors() : motionAvg{0} //: dht22(digitalSensorPin,DHTTYPE)
{
    /*if(digitalRead(isDigitalSensor)==HIGH)
    {
        humidityEnabled = true;
        dht22.begin();
        return;
    }
    humidityEnabled = false;*/
    pinMode(motionSensorPin,INPUT);
    motionIndex = 0;
    motionSensitivity = 40;
}

float Sensors::getHumidity()
{
    return 0;//dht22.readHumidity();
}

float Sensors::getTemperature()
{
    return 0;//dht22.readTemperature();
}

bool Sensors::isTemperatureEnabled()
{
    return false;
}

bool Sensors::isHumidityEnabled()
{
    return false;
}

bool Sensors::isMotionEnabled()
{
    return true;
}

int Sensors::getMotion()
{
    motionAvg[motionIndex] = digitalRead(motionSensorPin);
    if((++motionIndex)>19)
    {
        motionIndex = 0;
    }
    int sum = 0;
    for(int i = 0; i < 20; i++)
    {
        sum += motionAvg[i];
    }
    return ((sum*100)/20)>motionSensitivity;
}

int Sensors::getMotionSensitivity()
{
    return motionSensitivity;
}

void Sensors::setMotionSensitivity(int sensitivity)
{
    motionSensitivity = sensitivity;
}