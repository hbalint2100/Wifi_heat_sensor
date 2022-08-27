#include "WebserverTask.h"

static const char content[] PROGMEM = "<!DOCTYPE html><html><head><title>404 - Page not found!</title> <meta charset=\"UTF-8\"></head><body><h1>404 - Requested page not found!</h1></body></html>";

WebserverTask::WebserverTask(int port) : SystemControlledTask("WebserverTask"), webserver(port)
{
    updateserver.setup(&webserver);
}

void WebserverTask::notFound()
{
    webserver.send(404,"text/html",content);
}

void WebserverTask::root()
{
    File html = LittleFS.open("/www/index.html","r");
    if(!html||!html.available())
    {
        notFound();
        return;
    }
    webserver.send(200,"text/html",html.readString());
    html.close();
}

void WebserverTask::api()
{
    Serial.println(webserver.uri());
    Serial.println("Plain:"+webserver.arg("plain"));
    for(int i = 0; i<webserver.args();i++)
    {
        Serial.println(webserver.argName(i)+":"+webserver.arg(i));
    }
    for(int i = 0; i < webserver.headers();i++)
    {
        Serial.println("Header"+i + ':'+webserver.header(i));
    }
}

void WebserverTask::apiWrapper(WebserverTask *instance)
{
    instance->api();
}

void WebserverTask::rootWrapper(WebserverTask *instance)
{
    instance->root();
}

void WebserverTask::notFoundWrapper(WebserverTask *instance)
{
    instance->notFound();
}

void WebserverTask::setup()
{
    webserver.on("/",HTTP_GET,std::bind(&WebserverTask::rootWrapper,this));
    webserver.on("/api",std::bind(&WebserverTask::apiWrapper,this));
    webserver.onNotFound(std::bind(&WebserverTask::notFoundWrapper,this));
    webserver.begin();
    Serial.println("Webserver started");
}

void WebserverTask::loop()
{
    webserver.handleClient();
}

void WebserverTask::stop()
{
    webserver.stop();
    webserver.close();
}