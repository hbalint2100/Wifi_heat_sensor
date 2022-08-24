#include "System.h"
#include "LittleFS.h"
#include <Arduino.h>
#include "Scheduler.h"
#include "user_interface.h"

bool SystemClass::fileSystemMounted = false;
Wifi SystemClass::wifiCtrl;
MQTT SystemClass::mqttCtrl;
Messenger SystemClass::messenger;
SystemControlledTask* SystemClass::tasks = nullptr;
unsigned long SystemClass::lastSleep = 120000L;

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

Messenger& SystemClass::getMessenger()
{
    return messenger;
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

bool SystemClass::wakeUpFromDS()
{
    rst_info *info = system_get_rst_info();
    if(info)
    {
        return info->reason==REASON_DEEP_SLEEP_AWAKE;
    }
    return false;
}

uint32 SystemClass::RTCmillis()
{
    return system_get_rtc_time()*(((system_rtc_clock_cali_proc()*1000)>>12)/12);
}

void SystemClass::wake()
{
    Serial.println("Wake up");
    Serial.flush();
    wifiCtrl.enable();
    lastSleep = 0;
}

void SystemClass::sleep(unsigned timeInSeconds)
{
    if(timeInSeconds<1&&timeInSeconds*1000000L>=ESP.deepSleepMax())
    {
        return;
    }
    Serial.println("BYE");
    delay(30);
    wifiCtrl.disable();
    ESP.deepSleep(timeInSeconds*1000000L,RF_DEFAULT);
}

void SystemClass::restart()
{
    ESP.restart();
}