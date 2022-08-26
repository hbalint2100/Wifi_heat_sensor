#include "Scheduler.h"
#include "WebserverTask.h"
#include "WifiscanTask.h"
#include "SensingTask.h"
#include "SystemTask.h"
#include "MqttTask.h"
#include "Messenger.h"
#include "System.h"

void setup() 
{
  // put your setup code here, to run once:
  System.initializeSerial();
  System.mountFileSystem();
  System.initializePins();
  WebserverTask webserverTask(80);
  if(System.wakeUpFromDS())
  {
    System.wake();
    webserverTask.disable();
  }
  System.getWifiCtrl().getWifiData();
  System.getWifiCtrl().connect();
  System.getMqttCtrl().getMqttData();
  WifiscanTask wifiscanTask;
  MqttTask mqttTask;
  SensingTask sensingTask;
  SystemTask systemTask;
  System.addTask(&webserverTask);
  System.addTask(&wifiscanTask);
  System.getMessenger().registerTask(mqttTask);
  System.getMessenger().registerTask(sensingTask);
  System.getMessenger().registerTask(systemTask);
  Scheduler.start(&sensingTask);
  Scheduler.start(&webserverTask);
  Scheduler.start(&wifiscanTask);
  Scheduler.start(&mqttTask);
  Scheduler.start(&systemTask);
  Scheduler.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}