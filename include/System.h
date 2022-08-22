#pragma once
#include "Wifi.h"
#include "MQTT.h"
#include "SystemControlledTask.h"

class SystemClass
{
    private:
    static bool fileSystemMounted;
    static Wifi wifiCtrl;
    static MQTT mqttCtrl;
    static SystemControlledTask* tasks;
    public:
    static void mountFileSystem();
    static void initializeSerial();
    static void initializePins();
    static Wifi& getWifiCtrl();
    static MQTT& getMqttCtrl();
    static void addTask(SystemControlledTask *task);
    static SystemControlledTask* getTaskWithId(String ID);
    static void restart();
};

extern SystemClass System;