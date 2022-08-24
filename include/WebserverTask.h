#pragma once
#include "SystemControlledTask.h"
#include "MessengerInterface.h"
#include "ESP8266WebServer.h"
#include "ESP8266HTTPUpdateServer.h"
#include "LittleFS.h"

class WebserverTask : public SystemControlledTask, public MessengerInterface
{
    private:
    ESP8266WebServer webserver;
    ESP8266HTTPUpdateServer updateserver;
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