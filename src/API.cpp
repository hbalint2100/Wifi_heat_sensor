#include "API.h"
#include "AdvancedString.h"

APIResponse API::resolve(const HTTPMethod& method, APIRequestArg *args,unsigned size)
{
    String value;
    if(method==HTTP_GET&&GET("src",value,args,size))
    {
        value.toLowerCase();
        if(value=="sensor")
        {
            //todo
        }
        else if(value=="wifi")
        {
            //todo
        }
        else if(value=="system")
        {
            //todo
        }
    }
    return {200,"text/html","OK"};
}

bool API::GET(String argName,String& argValue,APIRequestArg* args,unsigned size)
{
    if(!args)
    {
        return false;
    }
    for(unsigned i = 0; i < size;i++)
    {
        if(args[i].name==argName)
        {
            argValue = args[i].value;
            return true;
        }
    }
    return false;
}