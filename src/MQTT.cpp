#include "MQTT.h"
#define CONF_PATH "/config"
static const String route = "HUSensor/";

MQTT::MQTT()
{
    set = false;
    mqttClient.setClient(wifiClient);
    mqttClient.setKeepAlive(150);
}

bool MQTT::isSet()
{
    return set;
}

bool MQTT::connect()
{
    if(!deviceName.isEmpty()&&!username.isEmpty()&&!password.isEmpty()&&mqttClient.connect(deviceName.c_str(),username.c_str(),password.c_str()))
    {
        Serial.println("MQTT connected");
        return true;
    }
    Serial.println("MQTT couldn't connect");
    return false;
}

String MQTT::getRoute()
{
    return route+deviceName+'/';
}

void MQTT::getMqttData()
{
    if(LittleFS.exists(CONF_PATH))
    {
        File config = LittleFS.open(CONF_PATH,"r");
        if(!config)
        {
            Serial.println("Config file couldn't be opened");
        }
        else
        {
            String line;
            String _brokerIP;
            String _port;
            String _username;
            String _password;
            String _deviceName;
            int startPos;
            while(config.available())
            {
                line = config.readStringUntil('\n');
                line.trim();
                if((line.startsWith("MQTT_BROKER_IP")||line.startsWith("mqtt_broker_ip"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    _brokerIP = line.substring(startPos+1);
                    _brokerIP.trim();
                    brokerIP = _brokerIP;
                }
                else if((line.startsWith("MQTT_BROKER_PORT")||line.startsWith("mqtt_broker_port"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    _port = line.substring(startPos+1);
                    _port.trim();
                    brokerPort = atoi(_port.c_str());
                }
                else if((line.startsWith("MQTT_USERNAME")||line.startsWith("mqtt_username"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    _username = line.substring(startPos+1);
                    _username.trim();
                    username = _username;
                }
                else if((line.startsWith("MQTT_PASSWORD")||line.startsWith("mqtt_password"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    _password = line.substring(startPos+1);
                    _password.trim();
                    password = _password;
                }
                else if((line.startsWith("MQTT_DEVICENAME")||line.startsWith("mqtt_devicename"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    _deviceName = line.substring(startPos+1);
                    _deviceName.trim();
                    deviceName = _deviceName;
                }
            }
            config.close();
            //direct String.c_str() causes error
            IPAddress ip;
            ip.fromString(_brokerIP);
            mqttClient.setServer(ip,brokerPort);
            if(_brokerIP!=emptyString&&_port!=emptyString&&_deviceName!=emptyString)
            {
                set = true;
            }
        }
    }
}

bool setMqttData(String typeName,String value)
{
    bool success = false;
    if(LittleFS.exists(CONF_PATH))
    {
        File config = LittleFS.open(CONF_PATH,"r");
        if(!config)
        {
            Serial.println("Config file couldn't be opened");
            return false;
        }
        else
        {
            String file;
            String line;
            int startPos;
            while(config.available())
            {
                line = config.readStringUntil('\n');
                if(line.startsWith(typeName)&&AdvancedString::findSubString(line,"=",startPos))
                {
                    line = line.substring(0,startPos+1);
                    line += value;
                    success = true;
                }
                file += line + '\n';
            }
            if(!success)
            {
                file += typeName + "=" + value;
                success = true;
            }
            config.close();
            config = LittleFS.open(CONF_PATH,"w");
            config.print(file);
            config.close();
        }
    }
    return success;
}

PubSubClient& MQTT::getClient()
{
    return mqttClient;
}

MQTT::~MQTT()
{
    if(mqttClient.connected())
    {
        mqttClient.disconnect();
    }
}

const String& MQTT::getDeviceName()
{
    return deviceName;
}

const String& MQTT::getBrokerIP()
{
    return brokerIP;
}

const String& MQTT::getUsername()
{
    return username;
}

unsigned MQTT::getBrokerPort()
{
    return brokerPort;
}

bool MQTT::setUsername(const String& _username)
{
    username = _username;
    return setMqttData("MQTT_USERNAME",_username);
}

bool MQTT::setPassword(const String& _password)
{
    password = _password;
    return setMqttData("MQTT_PASSWORD",_password);
}

bool MQTT::setDeviceName(const String& _deviceName)
{
    deviceName = _deviceName;
    return setMqttData("MQTT_DEVICENAME",_deviceName);
}

bool MQTT::setBrokerIP(const String& _brokerIP)
{
    brokerIP = _brokerIP;
    return setMqttData("MQTT_BROKER_IP",_brokerIP);
}

bool MQTT::setBrokerPort(unsigned port)
{
    if(port==0)
    {
        return false;
    }
    brokerPort = port;
    return setMqttData("MQTT_BROKER_PORT",String(port));
}

bool MQTT::loadConfig()
{
    set = false;
    IPAddress ip;
    ip.fromString(brokerIP);
    mqttClient.setServer(ip,brokerPort);
    set = true;
    connect();
    return true;
}