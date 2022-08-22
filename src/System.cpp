#include "System.h"
#include "LittleFS.h"
#include <Arduino.h>
#include "Scheduler.h"

bool SystemClass::fileSystemMounted = false;
Wifi SystemClass::wifiCtrl;
MQTT SystemClass::mqttCtrl;
SystemControlledTask* SystemClass::tasks = nullptr;

void SystemClass::initializeSerial()
{
    Serial.begin(9600);
    delay(50);
    Serial.println();
}

void SystemClass::mountFileSystem()
{
    if(fileSystemMounted)
    {
        return;
    }
    LittleFSConfig cfg;
    cfg.setAutoFormat(true);
    LittleFS.setConfig(cfg);
    if(!LittleFS.begin())
    {
        Serial.println("File system mount error");
        return;
    }
    fileSystemMounted = true;
}

void SystemClass::initializePins()
{
    pinMode(Wifi::wifiStatusLed,OUTPUT);
    digitalWrite(Wifi::wifiStatusLed,HIGH);
}

Wifi& SystemClass::getWifiCtrl()
{
    return wifiCtrl;
}

MQTT& SystemClass::getMqttCtrl()
{
    return mqttCtrl;
}

void SystemClass::addTask(SystemControlledTask *task)
{
    task->next = tasks;
    tasks = task;
}

//Possible nullptr
SystemControlledTask* SystemClass::getTaskWithId(String Id)
{
    for(SystemControlledTask* current = tasks;current!=nullptr;current=current->next)
    {
        if(current->systemID==Id)
        {
            return current;
        }
    }
    return nullptr;
}

void SystemClass::restart()
{
    ESP.restart();
}