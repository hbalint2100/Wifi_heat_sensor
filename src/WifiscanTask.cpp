#include "WifiscanTask.h"
#include "System.h"
#include <Arduino.h>

void WifiscanTask::setup()
{
    if(System.getWifiCtrl().getSSID().isEmpty())
    {
        disable();
    }
    setInterval(10000L);
    Serial.println("Wifi scan task started");
}

void WifiscanTask::loop()
{
    if((WiFi.getMode()==WIFI_AP||WiFi.getMode()==WIFI_AP_STA)&&WiFi.status()!=WL_CONNECTED&&WiFi.softAPgetStationNum()==0)
    {
        int networks = WiFi.scanNetworks();
        for(int i = 0; i < networks; i++)
        {
            if(WiFi.SSID(i)==System.getWifiCtrl().getSSID())
            {
                System.getWifiCtrl().connect();
                break;
            }
        }
    }
    else if(WiFi.getMode()==WIFI_STA&&getInterval()!=40000L)
    {
        setInterval(40000L);
    }
}