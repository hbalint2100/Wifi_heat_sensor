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
    else if(method==HTTP_POST&&GET("plain",value,args,size))
    {
        String dst;
        if((AdvancedString::findSubString(value,"\"dst\"",",",dst)||AdvancedString::findSubString(value,"\"dst\"","}",dst)))
        {
            dst.toLowerCase();
            int pos;
            if(AdvancedString::findSubString(dst,"\"wifi\"",pos))
            {
                if(setWifiData(value))
                {
                    return {200,"application/json","{\"success\": true}"};
                }
                else
                {
                    return {200,"application/json","{\"success\": false}"};
                }
            }
            else if(AdvancedString::findSubString(dst,"\"mqtt\"",pos))
            {
                if(setMqttData(value))
                {
                    return {200,"application/json","{\"success\": true}"};
                }
                else
                {
                    return {200,"application/json","{\"success\": false}"};
                }
            }
        }
    }
    return {404,"application/json","{}"};
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

bool API::setWifiData(const String& json)
{
    String line;
    int success = 0;
    int tried = 0;
    if(AdvancedString::findSubString(json,"\"ssid\"",",",line,false)||AdvancedString::findSubString(json,"\"ssid\"","}",line,false))
    {
        String value;
        if(AdvancedString::findSubString(line,"\"","\"",value))
        {
            tried++;
            if(wifi.setSSID(value)&&wifi.loadConfig())
            {
                success++;
            }
        }
    }
    if(AdvancedString::findSubString(json,"\"passwd\"",",",line,false)||AdvancedString::findSubString(json,"\"passwd\"","}",line,false))
    {
        String value;
        if(AdvancedString::findSubString(line,"\"","\"",value))
        {
            tried++;
            if(wifi.setPASSWD(value)&&wifi.loadConfig())
            {
                success++;
            }
        }
    }
    if(AdvancedString::findSubString(json,"\"gatewayIP\"",",",line,false)||AdvancedString::findSubString(json,"\"gatewayIP\"","}",line,false))
    {
        String value;
        if(AdvancedString::findSubString(line,"\"","\"",value))
        {
            tried++;
            if(wifi.setGatewayIP(value)&&wifi.loadConfig())
            {
                success++;
            }
        }
    }
    if(AdvancedString::findSubString(json,"\"subnetMask\"",",",line,false)||AdvancedString::findSubString(json,"\"subnetMask\"","}",line,false))
    {
        String value;
        if(AdvancedString::findSubString(line,"\"","\"",value))
        {
            tried++;
            if(wifi.setSubnetMask(value)&&wifi.loadConfig())
            {
                success++;
            }
        }
    }
    if(AdvancedString::findSubString(json,"\"staticIP\"",",",line,false)||AdvancedString::findSubString(json,"\"staticIP\"","}",line,false))
    {
        String value;
        if(AdvancedString::findSubString(line,"\"","\"",value))
        {
            tried++;
            if(wifi.setStaticIP(value)&&wifi.loadConfig())
            {
                success++;
            }
        }
    }
    return success==tried&&success!=0;
}

bool API::setMqttData(const String& json)
{   
    String line;
    int success = 0;
    int tried = 0;
    if(AdvancedString::findSubString(json,"\"brokerIP\"",",",line,false)||AdvancedString::findSubString(json,"\"brokerIP\"","}",line,false))
    {
        String value;
        if(AdvancedString::findSubString(line,"\"","\"",value))
        {
            tried++;
            if(mqtt.setBrokerIP(value)&&mqtt.loadConfig())
            {
                success++;
            }
        }
    }
    if(AdvancedString::findSubString(json,"\"brokerPort\"",",",line,false)||AdvancedString::findSubString(json,"\"brokerPort\"","}",line,false))
    {
        String value;
        int pos;
        AdvancedString::findSubString(line,":",pos);       
        value = line.substring(pos+1);
        value.trim();
        if(value.isEmpty())
        {
            return false;
        }
        tried++;
        if(mqtt.setBrokerPort(atoi(value.c_str()))&&mqtt.loadConfig())
        {
            success++;
        }
    }
    if(AdvancedString::findSubString(json,"\"deviceName\"",",",line,false)||AdvancedString::findSubString(json,"\"deviceName\"","}",line,false))
    {
        String value;
        if(AdvancedString::findSubString(line,"\"","\"",value))
        {
            tried++;
            if(mqtt.setDeviceName(value)&&mqtt.loadConfig())
            {
                success++;
            }
        }
    }
    if(AdvancedString::findSubString(json,"\"password\"",",",line,false)||AdvancedString::findSubString(json,"\"password\"","}",line,false))
    {
        String value;
        if(AdvancedString::findSubString(line,"\"","\"",value))
        {
            tried++;
            if(mqtt.setPassword(value)&&mqtt.loadConfig())
            {
                success++;
            }
        }
    }
    if(AdvancedString::findSubString(json,"\"username\"",",",line,false)||AdvancedString::findSubString(json,"\"username\"","}",line,false))
    {
        String value;
        if(AdvancedString::findSubString(line,"\"","\"",value))
        {
            tried++;
            if(mqtt.setUsername(value)&&mqtt.loadConfig())
            {
                success++;
            }
        }
    }
    return success==tried&&success!=0;
}