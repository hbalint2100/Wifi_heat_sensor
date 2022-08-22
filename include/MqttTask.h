#pragma once
#include "SystemControlledTask.h"
#include "MessengerInterface.h"

class MqttTask : public SystemControlledTask, public MessengerInterface
{
    public:
    MqttTask() : SystemControlledTask("MqttTask"){}
    void setup();
    void loop();
};