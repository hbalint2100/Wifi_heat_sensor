#pragma once
#include "SystemControlledTask.h"

class WifiscanTask : public SystemControlledTask
{
    public:
    WifiscanTask() : SystemControlledTask("WifiscanTask"){}
    void setup();
    void loop();
};