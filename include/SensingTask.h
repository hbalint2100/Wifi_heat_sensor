#pragma once
#include "MessengerInterface.h"
#include "LeanTask.h"

class SensingTask : public LeanTask, public MessengerInterface
{
    public:
    void setup();
    void loop();
};