#pragma once
#include "LeanTask.h"
#include "ESP8266WebServer.h"
#include "LittleFS.h"

class WebserverTask : public LeanTask
{
    private:
    ESP8266WebServer webserver;
    void notFound();
    void root();
    void api();
    static void notFoundWrapper(WebserverTask*);
    static void rootWrapper(WebserverTask*);
    static void apiWrapper(WebserverTask*);

    public:
    WebserverTask(int port);
    void setup();
    void loop();
    void stop();
};