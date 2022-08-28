#pragma once

class APISensorInterface
{

    public:
    virtual bool isTemperatureEnabled() = 0;
    virtual bool isHumidityEnabled() = 0;
    virtual float getTemperature() = 0;
    virtual float getHumidity() = 0;
};