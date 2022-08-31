#include "SystemTask.h"
#include "System.h"

void SystemTask::loop()
{
    if((WiFi.getMode()==WIFI_AP_STA||WiFi.getMode()==WIFI_STA)
    &&System.getMqttCtrl().getClient().connected()
    &&millis()>System.lastSleep)
    {
        Message messages[5];
        receiveMessage(messages,5,"System");
        bool success = false;
        for(int i = 0; i < 5;i++)
        {
            if(messages[i].getMessageText()=="All data successfully sent")
            {
                success = true;
                break;
            }
        }
        if(success&&System.getMessenger().isEmpty())
        {
            System.sleep(200);
        }
    }
    if(WiFi.getMode()==WIFI_STA&&millis()>300000L)
    {
        SystemControlledTask* task = System.getTaskWithId("WebserverTask");
        if(task&&task->isEnabled())
        {
        task->disable();
        Serial.println("Webserver disabled");
        }
    }
    else if((WiFi.getMode()==WIFI_AP||WiFi.getMode()==WIFI_AP_STA))
    {
        SystemControlledTask* task = System.getTaskWithId("WebserverTask");
        if(task&&!task->isEnabled())
        {
        task->enable();
        Serial.println("Webserver enabled");
        }
    }
}