#pragma once
#include "MessengerInterface.h"
#include "LeanTask.h"
#define SENSORPIN D7

class SensingTask : public LeanTask, public MessengerInterface
{
    public:
    void setup();
    void loop();
};