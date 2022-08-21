#include <Arduino.h>
#include "Wifi.h"
#include "Scheduler.h"
#include "WebserverTask.h"
#include "WifiscanTask.h"
#include "MqttTask.h"
#include "LittleFS.h"
#include "Messenger.h"

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(50);
  Serial.println();
  system_set_os_print(true);
  LittleFSConfig cfg;
  cfg.setAutoFormat(true);
  LittleFS.setConfig(cfg);
  if(!LittleFS.begin())
  {
    Serial.println("File system mount error");
    return;
  }
  pinMode(Wifi::wifiStatusLed,OUTPUT);
  digitalWrite(Wifi::wifiStatusLed,HIGH);
  delay(200);
  Messenger messenger;
  Wifi wifiCtrl;
  wifiCtrl.getWifiData();
  wifiCtrl.connect();
  WebserverTask webserverTask(80);
  WifiscanTask wifiscanTask(wifiCtrl);
  MqttTask mqttTask;
  messenger.registerTask(mqttTask);
  Scheduler.start(&webserverTask);
  Scheduler.start(&wifiscanTask);
  Scheduler.start(&mqttTask);
  Scheduler.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}
