#include "Scheduler.h"
#include "WebserverTask.h"
#include "WifiscanTask.h"
#include "MqttTask.h"
#include "Messenger.h"
#include "System.h"

void setup() 
{
  // put your setup code here, to run once:
  System.initializeSerial();
  System.mountFileSystem();
  System.initializePins();
  System.getWifiCtrl().getWifiData();
  System.getWifiCtrl().connect();
  System.getMqttCtrl().getMqttData();
  pinMode(0,INPUT);
  WebserverTask webserverTask(80);
  WifiscanTask wifiscanTask;
  MqttTask mqttTask;
  Messenger messenger;
  messenger.registerTask(mqttTask);
  Scheduler.start(&webserverTask);
  Scheduler.start(&wifiscanTask);
  Scheduler.start(&mqttTask);
  Scheduler.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}