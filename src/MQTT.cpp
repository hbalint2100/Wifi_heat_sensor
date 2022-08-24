#include "MQTT.h"
#define CONF_PATH "/config"
static const String productName = "HUSensor";

MQTT::MQTT()
{
    set = false;
    mqttClient.setClient(wifiClient);
    mqttClient.setKeepAlive(900);
}

bool MQTT::isSet()
{
    return set;
}

bool MQTT::connect()
{
    String willTopic = productName+"/"+deviceName+"/status";
    if(!deviceName.isEmpty()&&!username.isEmpty()&&!password.isEmpty()&&mqttClient.connect(deviceName.c_str(),username.c_str(),password.c_str(),willTopic.c_str(),2,true,"Offline"))
    {
        Serial.println("MQTT connected");
        mqttClient.publish(willTopic.c_str(),"Online",true);
        return true;
    }
    Serial.println("MQTT couldn't connect");
    return false;
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
                if((line.startsWith("MQTT_BROKER_IP")||line.startsWith("broker_ip"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    _brokerIP = line.substring(startPos+1);
                    _brokerIP.trim();
                }
                else if((line.startsWith("MQTT_BROKER_PORT")||line.startsWith("mqtt_broker_port"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    _port = line.substring(startPos+1);
                    _port.trim();
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
            mqttClient.setServer(ip,atoi(_port.c_str()));
            if(_brokerIP!=emptyString&&_port!=emptyString&&_deviceName!=emptyString)
            {
                set = true;
            }
        }
    }
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