#pragma once
#include <Arduino.h>
#include "LeanTask.h"
#include "Wifi.h"

class WifiscanTask : public LeanTask
{
    private:
    Wifi wifiCtrl;
    unsigned long lastCheck;
    public:
    WifiscanTask(Wifi _wifiCtrl) : wifiCtrl(_wifiCtrl),lastCheck(0){};
    void setup();
    void loop();
};