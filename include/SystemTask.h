#pragma once
#include "LeanTask.h"
#include "MessengerInterface.h"

class SystemTask : public LeanTask, public MessengerInterface
{
    public:
    void loop();
};