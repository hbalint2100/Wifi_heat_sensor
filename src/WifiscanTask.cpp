#include "WifiscanTask.h"

void WifiscanTask::setup()
{
    if(wifiCtrl.getSSID().isEmpty())
    {
        disable();
    }
    setInterval(20000L);
    Serial.println("Scan task started");
}

void WifiscanTask::loop()
{
    if((WiFi.getMode()==WIFI_AP||WiFi.getMode()==WIFI_AP_STA)&&WiFi.status()!=WL_CONNECTED&&WiFi.softAPgetStationNum()==0&&millis()-lastCheck>=20000L)
    {
        int networks = WiFi.scanNetworks();
        Serial.println("Scan run");
        for(int i = 0; i < networks; i++)
        {
            if(WiFi.SSID(i)==wifiCtrl.getSSID())
            {
                wifiCtrl.connect();
            }
        }
        lastCheck = millis();
    }
    Serial.println("Scan task run");
}