#pragma once
#include "ESP8266WebServer.h"

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
    bool GET(String argName,String& argValue,APIRequestArg* args,unsigned size);
    public:
    APIResponse resolve(const HTTPMethod& method,APIRequestArg*,unsigned size);
};