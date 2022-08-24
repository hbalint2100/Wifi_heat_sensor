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
            }
            config.close();
        }
    }
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
    if(WiFi.status()!=WL_CONNECTED)
    {
        if(!SSID.isEmpty()&&wifiSTAMode())
        {
            return;
        }
        wifiAPMode();
    }
}

bool Wifi::disconnect()
{
    return WiFi.disconnect(true);
}

void Wifi::setPASSWD(const String& PASSWD)
{
    this->PASSWD = PASSWD;
}

void Wifi::setSSID(const String& SSID)
{
    this->SSID = SSID;
}

String Wifi::getPASSWD()
{
    return PASSWD;
}

String Wifi::getSSID()
{
    return SSID;
}