#pragma once
#include "Wifi.h"
#include "MQTT.h"
#include "SystemControlledTask.h"
#include "Messenger.h"
#include "Sensors.h"
#include "MessengerInterface.h"

class SystemClass : public MessengerInterface
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
    static void restart();
    static void sleep(unsigned timeInSeconds);
};

extern SystemClass System;