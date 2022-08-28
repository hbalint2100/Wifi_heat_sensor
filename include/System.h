#pragma once
#include "Wifi.h"
#include "MQTT.h"
#include "SystemControlledTask.h"
#include "Messenger.h"
#include "Sensors.h"
#include "APISystemInterface.h"

class SystemClass : public APISystemInterface
{
    private:
    static bool fileSystemMounted;
    static Wifi wifiCtrl;
    static MQTT mqttCtrl;
    static Sensors sensorCtrl;
    static Messenger messenger;
    static SystemControlledTask* tasks;
    public:
    static void wake();
    static bool wakeUpFromDS();
    static unsigned long lastSleep;
    static void mountFileSystem();
    static void initializeSerial();
    static void initializePins();
    static uint32 RTCmillis();
    static Wifi& getWifiCtrl();
    static MQTT& getMqttCtrl();
    static Sensors& getSensorCtrl();
    static Messenger& getMessenger();
    static void addTask(SystemControlledTask *task);
    static SystemControlledTask* getTaskWithId(String ID);
    void restart();
    unsigned long getSystemUpTime();
    static void sleep(unsigned timeInSeconds);
};

extern SystemClass System;