#pragma once

class APISensorInterface
{

    public:
    virtual bool isTemperatureEnabled() = 0;
    virtual bool isHumidityEnabled() = 0;
    virtual bool isMotionEnabled() = 0;
    virtual float getTemperature() = 0;
    virtual float getHumidity() = 0;
    virtual int getMotion() = 0;
    virtual int getMotionSensitivity() = 0;
};