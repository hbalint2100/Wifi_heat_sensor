#include "WifiscanTask.h"

void WifiscanTask::setup()
{
    if(wifiCtrl.getSSID().isEmpty())
    {
        disable();
    }
    setInterval(10000L);
    Serial.println("Scan task started");
}

void WifiscanTask::loop()
{
    if((WiFi.getMode()==WIFI_AP||WiFi.getMode()==WIFI_AP_STA)&&WiFi.status()!=WL_CONNECTED&&WiFi.softAPgetStationNum()==0&&millis()-lastCheck>=10000L)
    {
        int networks = WiFi.scanNetworks();
        for(int i = 0; i < networks; i++)
        {
            if(WiFi.SSID(i)==wifiCtrl.getSSID())
            {
                wifiCtrl.connect();
            }
        }
        lastCheck = millis();
    }
    else if(WiFi.getMode()==WIFI_STA)
    {
        setInterval(40000L);
    }
}