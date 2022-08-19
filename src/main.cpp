#include <Arduino.h>
#include "Wifi.h"
#include "Scheduler.h"
#include "WebserverTask.h"
#include "LittleFS.h"

Wifi wifiCtrl;
WebserverTask webserverTask(80);
bool blink = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(50);
  Serial.println();
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
  wifiCtrl.getWifiData();
  wifiCtrl.connect();
  Scheduler.start(&webserverTask);
  Scheduler.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}
