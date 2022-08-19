#include "Wifi.h"
#define CONF_PATH "/config"

WiFiEventHandler connectedHandler, disconnectedHandler;

Wifi::Wifi(){}

Wifi::Wifi(const String& SSID,const String& PASSWD)
{
    setPASSWD(PASSWD);
    setSSID(SSID);
}

bool Wifi::enable()
{
    return WiFi.mode(WIFI_STA);
}

bool Wifi::disable()
{
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

void Wifi::wifiSTAMode()
{
    connectedHandler = WiFi.onStationModeConnected([](const WiFiEventStationModeConnected& event)
    {
        WiFi.printDiag(Serial);
        digitalWrite(wifiStatusLed,LOW);
    });
    disconnectedHandler = WiFi.onStationModeDisconnected([this](const WiFiEventStationModeDisconnected& event)
    {
        disconnect();
    });

    WiFi.setPhyMode(WIFI_PHY_MODE_11N);
    WiFi.begin(this->SSID,this->PASSWD);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
}

void Wifi::wifiAPMode()
{   
    String SSID = "HUSensor_"+WiFi.softAPmacAddress().substring(0,5);
    WiFi.mode(WIFI_AP);
    WiFi.setPhyMode(WIFI_PHY_MODE_11G);
    IPAddress local_ip = IPAddress(192,168,1,1);
    IPAddress gateway = IPAddress(192,168,1,2);
    IPAddress subnet = IPAddress(255,255,255,0);
    WiFi.softAPConfig(local_ip,gateway,subnet);
    WiFi.softAP(SSID,emptyString,8,0,4);
    WiFi.waitForConnectResult();
    WiFi.printDiag(Serial);
    Serial.println(WiFi.softAPIP().toString());
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
    delay(10);
    if(WiFi.status()!=WL_CONNECTED&&!SSID.isEmpty())
    {
        wifiSTAMode();
    }
}

bool Wifi::disconnect()
{
    bool result = WiFi.disconnect(true);
    wifiAPMode();
    return result;
}

void Wifi::setPASSWD(const String& PASSWD)
{
    this->PASSWD = PASSWD;
}

void Wifi::setSSID(const String& SSID)
{
    this->SSID = SSID;
}