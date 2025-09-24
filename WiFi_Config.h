
#ifndef NETWORK_H
#define NETWORK_H

#include<Arduino.h>
#include<WiFi.h>
#include"Admin.h"
#include"OLED_Config.h"
#include"Keypad_Config.h"

extern char* ssidlist[10];
extern bool wifiStatus;

class WiFiManager{
  public:
    void wifi_config(bool frc);
    void wifi_begin();
  private:
    const char* net   = "WiFi";
    const char* key3  = "SSID";
    const char* key4  = "pass";
};

extern WiFiManager wifimanager;
// void wifi_config(const char* ssid, const char* password);

#endif



