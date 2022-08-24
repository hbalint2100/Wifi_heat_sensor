#include "WifiscanTask.h"
#include "System.h"
#include <Arduino.h>

void WifiscanTask::setup()
{
    if(System.getWifiCtrl().getSSID().isEmpty())
    {
        disable();
    }
    setInterval(2000L);
    Serial.println("Wifi scan task started");
}

void WifiscanTask::loop()
{
    if((WiFi.getMode()==WIFI_AP||WiFi.getMode()==WIFI_AP_STA)&&WiFi.softAPgetStationNum()==0)
    {
        if(WiFi.status()==WL_CONNECTED)
        {
            System.getWifiCtrl().disable();
        }
        Serial.println("Wifi scan");
        WiFi.mode(WIFI_AP_STA);
        WiFi.setOutputPower(20.5);
        int networks = WiFi.scanNetworks();
        for(int i = 0; i < networks; i++)
        {
            Serial.println(WiFi.SSID(i));
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