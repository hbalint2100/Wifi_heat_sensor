#pragma once
#include "ESP8266WebServer.h"
#include "APISensorInterface.h"
#include "APIWifiInterface.h"
#include "APIMqttInterface.h"
#include "APISystemInterface.h"

typedef struct APIResponse{
    unsigned httpCode;
    String contentType;
    String content;
} APIResponse;

typedef struct APIRequestArg{
    String name;
    String value;
} APIRequestArg;

class API
{
    private:
    APISensorInterface& sensor;
    APIWifiInterface& wifi;
    APIMqttInterface& mqtt;
    APISystemInterface& system;
    bool GET(String argName,String& argValue,APIRequestArg* args,unsigned size);
    bool getSensorData(APIRequestArg *args,unsigned size,String& response);
    bool getWifiData(APIRequestArg *args,unsigned size,String& response);
    bool setWifiData(const String& request);
    bool getMqttData(APIRequestArg *args,unsigned size,String& response);
    bool setMqttData(const String& request);
    bool getSystemData(APIRequestArg *args,unsigned size,String& response);
    public:
    API(APISensorInterface& _sensor,APIWifiInterface& _wifi,APIMqttInterface& _mqtt,APISystemInterface& _system) 
    : sensor(_sensor), wifi(_wifi), mqtt(_mqtt), system(_system){}
    APIResponse resolve(const HTTPMethod& method,APIRequestArg*,unsigned size);
};