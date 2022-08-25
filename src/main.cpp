#include "Scheduler.h"
#include "WebserverTask.h"
#include "WifiscanTask.h"
#include "SensingTask.h"
#include "MqttTask.h"
#include "Messenger.h"
#include "System.h"

void setup() 
{
  // put your setup code here, to run once:
  System.initializeSerial();
  System.mountFileSystem();
  System.initializePins();
  if(System.wakeUpFromDS())
  {
    System.wake();
  }
  System.getWifiCtrl().getWifiData();
  System.getWifiCtrl().connect();
  System.getMqttCtrl().getMqttData();
  WebserverTask webserverTask(80);
  WifiscanTask wifiscanTask;
  MqttTask mqttTask;
  SensingTask sensingTask;
  System.addTask(&webserverTask);
  System.addTask(&wifiscanTask);
  System.getMessenger().registerTask(mqttTask);
  System.getMessenger().registerTask(sensingTask);
  Scheduler.start(&sensingTask);
  Scheduler.start(&webserverTask);
  Scheduler.start(&wifiscanTask);
  Scheduler.start(&mqttTask);
  Scheduler.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if((WiFi.getMode()==WIFI_AP_STA||WiFi.getMode()==WIFI_STA)
  &&System.getMqttCtrl().getClient().connected()
  &&millis()>System.lastSleep&&millis()-System.lastSleep>45000L)
  {
    if(!System.getMessenger().isEmpty())
    {
      //todo
    }
    Serial.println("Millis:"+String(millis()));
    Serial.println("Last sleep:"+String(System.lastSleep));
    Serial.flush();
    delay(50);
    System.sleep(240);
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