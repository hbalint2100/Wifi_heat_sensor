#include "Wifi.h"
#define CONF_PATH "/config"

WiFiEventHandler connectedHandler, disconnectedHandler;

Wifi::Wifi()
{
    disabled = true;
}

Wifi::Wifi(const String& SSID,const String& PASSWD)
{
    disabled = true;
    setPASSWD(PASSWD);
    setSSID(SSID);
}

bool Wifi::forcedApMode()
{
    return digitalRead(forcedApModePin) == LOW;
}

bool Wifi::enable()
{
    disabled = false;
    return true;
}

bool Wifi::disable()
{
    disabled = true;
    digitalWrite(wifiStatusLed,HIGH);
    delay(50);
    return WiFi.mode(WIFI_OFF);
}

void Wifi::getWifiData()
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
            String ssid;
            String passwd;
            String s_staticIp;
            String s_subnetMask;
            String s_gatewayIp;
            int startPos;
            while(config.available())
            {
                line = config.readStringUntil('\n');
                line.trim();
                if((line.startsWith("SSID")||line.startsWith("ssid"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    ssid = line.substring(startPos+1);
                    ssid.trim();
                    setSSID(ssid);
                }
                else if((line.startsWith("PASSWD")||line.startsWith("passwd"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    passwd = line.substring(startPos+1);
                    passwd.trim();
                    setPASSWD(passwd);
                }
                else if((line.startsWith("STATIC_IP")||line.startsWith("static_ip"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    s_staticIp = line.substring(startPos+1);
                    s_staticIp.trim();
                    staticIP.fromString(s_staticIp);
                }
                else if((line.startsWith("SUBNET_MASK")||line.startsWith("subnet_mask"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    s_subnetMask = line.substring(startPos+1);
                    s_subnetMask.trim();
                    subnetMask.fromString(s_subnetMask);
                }
                else if((line.startsWith("GATEWAY_IP")||line.startsWith("gateway_ip"))&&AdvancedString::findSubString(line,"=",startPos))
                {
                    s_gatewayIp = line.substring(startPos+1);
                    s_gatewayIp.trim();
                    gateway.fromString(s_gatewayIp);
                }
            }
            config.close();
        }
    }
}

bool setWifiData(String typeName,String value)
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

bool Wifi::wifiSTAMode()
{
    if(disabled)
    {
        return false;
    }
    connectedHandler = WiFi.onStationModeConnected([](const WiFiEventStationModeConnected& event)
    {
        WiFi.printDiag(Serial);
        digitalWrite(wifiStatusLed,LOW);
    });
    disconnectedHandler = WiFi.onStationModeDisconnected([this](const WiFiEventStationModeDisconnected& event)
    {
        Serial.println("Disconnected");
        digitalWrite(wifiStatusLed,HIGH);
    });
    WiFi.setSleepMode(WIFI_LIGHT_SLEEP);
    WiFi.mode(WIFI_STA);
    WiFi.setOutputPower(20.5);
    WiFi.setPhyMode(WIFI_PHY_MODE_11N);
    if(staticIP.isSet()&&gateway.isSet()&&subnetMask.isSet())
    {
        WiFi.config(staticIP,gateway,subnetMask);
    }
    WiFi.begin(this->SSID,this->PASSWD);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    return WiFi.waitForConnectResult(30000L)==WL_CONNECTED;
}

void Wifi::wifiAPMode()
{   
    if(disabled)
    {
        return;
    }
    String SSID = "HUSensor_"+WiFi.softAPmacAddress().substring(0,5);
    WiFi.setAutoReconnect(false);
    WiFi.disconnect(true);
    WiFi.setSleepMode(WIFI_LIGHT_SLEEP,5);
    WiFi.mode(WIFI_AP);
    WiFi.setPhyMode(WIFI_PHY_MODE_11G);
    IPAddress local_ip = IPAddress(192,168,1,1);
    IPAddress gateway = IPAddress(192,168,1,1);
    IPAddress subnet = IPAddress(255,255,255,0);
    WiFi.softAPConfig(local_ip,gateway,subnet);
    WiFi.softAP(SSID,"",4,0,4);
    WiFi.printDiag(Serial);
    for (unsigned i = 0; i < 10; i++)
    {
        digitalWrite(wifiStatusLed,LOW);
        delay(100);
        digitalWrite(wifiStatusLed,HIGH);
        delay(100);
    }
}

void Wifi::connect()
{
    enable();
    Serial.println("Trying to connect...");
    if(WiFi.status()!=WL_CONNECTED)
    {
        if(!SSID.isEmpty()&&!forcedApMode()&&wifiSTAMode())
        {
            return;
        }
        if(WiFi.getMode()!=WIFI_AP&&WiFi.getMode()!=WIFI_AP_STA)
        {
            wifiAPMode();
        }
    }
}

bool Wifi::disconnect()
{
    return WiFi.disconnect(true);
}

bool Wifi::setPASSWD(const String& PASSWD)
{
    this->PASSWD = PASSWD;
    return setWifiData("PASSWD",PASSWD);
}

bool Wifi::setSSID(const String& SSID)
{
    this->SSID = SSID;
    return setWifiData("SSID",SSID);
}

const String& Wifi::getPASSWD()
{
    return PASSWD;
}

const String& Wifi::getSSID()
{
    return SSID;
}

bool Wifi::isConnected()
{
    return WiFi.status()==WL_CONNECTED;
}

bool Wifi::isDHCPEnabled()
{
    return !(staticIP.isSet()&&gateway.isSet()&&subnetMask.isSet());
}

String Wifi::getStaticIP()
{
    return staticIP.isSet()? staticIP.toString():"";
}

String Wifi::getGatewayIP()
{
    return gateway.isSet()? gateway.toString():"";
}

String Wifi::getSubnetMask()
{
    return subnetMask.isSet()? subnetMask.toString():"";
}

bool Wifi::setStaticIP(const String& _staticIP)
{
    return staticIP.fromString(_staticIP)&&setWifiData("STATIC_IP",_staticIP);
}

bool Wifi::setGatewayIP(const String& gatewayIP)
{
    return gateway.fromString(gatewayIP)&&setWifiData("GATEWAY_IP",gatewayIP);
}

bool Wifi::setSubnetMask(const String& _subnetMask)
{
    return subnetMask.fromString(_subnetMask)&&setWifiData("SUBNET_MASK",_subnetMask);
}

bool Wifi::loadConfig()
{
    connect();
    return true;
}