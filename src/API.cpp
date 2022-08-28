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
            String response = "{";
            if(getSensorData(args,size,response))
            {
                //remove comma
                response = response.substring(0,response.length()-1);
                response += '}';
                return {200,"application/json",response};
            }
        }
        else if(value=="wifi")
        {
            String response = "{";
            if(getWifiData(args,size,response))
            {
                //remove comma
                response = response.substring(0,response.length()-1);
                response += '}';
                return {200,"application/json",response};
            }
        }
        else if(value=="mqtt")
        {
            String response = "{";
            if(getMqttData(args,size,response))
            {
                response = response.substring(0,response.length()-1);
                response += '}';
                return {200,"application/json",response};
            }
        }
        else if(value=="system")
        {
            String response = "{";
            if(getSystemData(args,size,response))
            {
                response = response.substring(0,response.length()-1);
                response += '}';
                return {200,"application/json",response};
            }
        }
    }
    return {204,"application/json","{}"};
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

bool API::getSensorData(APIRequestArg *args,unsigned size,String& response)
{
    String value;
    bool success = false;
    if(GET("type",value,args,size))
    {
        value.toLowerCase();
       if((value=="humidity"||value=="all")&&sensor.isHumidityEnabled())
       {
            response += "\"humidity\": "+String(sensor.getHumidity())+',';
            success = true;
       }
       if((value=="temperature"||value=="all")&&sensor.isTemperatureEnabled())
       {
            response += "\"temperature\": "+String(sensor.getTemperature())+',';
            success = true;
       }
    }
    return success;
}

bool API::getWifiData(APIRequestArg *args,unsigned size,String& response)
{
    String value;
    bool success = false;
    if(GET("info",value,args,size))
    {
        value.toLowerCase();
        if(value=="ssid"||value=="all")
        {
            response += "\"ssid\": \""+wifi.getSSID()+"\",";
            success = true;
        }
        if(value=="dhcp"||value=="all")
        {
            response += "\"dhcp\": "+String(wifi.isDHCPEnabled()?"true":"false")+',';
            success = true;
        }
        if(value=="connection"||value=="all")
        {
            response += "\"connected\": "+String(wifi.isConnected()?"true":"false")+',';
            success = true;
        }
        if(value=="gatewayip"||value=="all"||value=="ip")
        {
            response += "\"gatewayIP\": \""+wifi.getGatewayIP()+"\",";
            success = true;
        }
        if(value=="subnetmask"||value=="all"||value=="ip")
        {
            response += "\"subnetMask\": \""+wifi.getSubnetMask()+"\",";
            success = true;
        }
        if(value=="staticip"||value=="all"||value=="ip")
        {
            response += "\"staticIP\": \""+wifi.getStaticIP()+"\",";
            success = true;
        }
    }
    return success;
}

bool API::getMqttData(APIRequestArg *args,unsigned size,String& response)
{
    String value;
    bool success = false;
    if(GET("info",value,args,size))
    {
        value.toLowerCase();
        if(value=="brokerip"||value=="all")
        {
           response += "\"brokerIP\": \""+mqtt.getBrokerIP()+"\",";
           success = true;
        }
        if(value=="brokerport"||value=="all")
        {
           response += "\"brokerPort\": "+String(mqtt.getBrokerPort())+',';
           success = true;
        }
        if(value=="devicename"||value=="all")
        {
            response += "\"deviceName\": \""+mqtt.getDeviceName()+"\","; 
            success = true;
        }
        if(value=="username"||value=="all")
        {
            response += "\"username\": \""+mqtt.getUsername()+"\",";
            success = true;
        }
    }
    return success;
}

bool API::getSystemData(APIRequestArg *args,unsigned size,String& response)
{
    String value;
    bool success = false;
    if(GET("action",value,args,size))
    {
        value.toLowerCase();
        if(value=="restart")
        {
           system.restart();
           success = true;
        }
    }
    else if(GET("info",value,args,size))
    {
        value.toLowerCase();
        if(value=="systemtime"||value=="all")
        {
            response += "\"systemTime\": "+String(system.getSystemUpTime())+",";
            success = true;
        }
    }
    return success;
}