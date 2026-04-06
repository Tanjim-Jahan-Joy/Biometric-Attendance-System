#ifndef ADMIN_H
#define ADMIN_H

#include<Arduino.h>
#include<Preferences.h>
#include"Keypad_Config.h"
#include"OLED_Config.h"
#include"FingerPrint_Config.h"
#include"Message_Passing.h"
#include"WiFi_Config.h"
#include"GSM_Config.h"

// extern TaskHandle_t AdminTaskHandle;
extern Preferences preferences;
extern String key;
extern String defaultPwd;
extern String DeviceID;
extern String Password;
extern String Uinput;
extern String star;
extern String UID;
extern bool check;
extern char* menu[];
extern unsigned long previousMillis;
extern const unsigned long interval;

class Manager{
  public:
    void begin();
    void setPassword();
    void setDevID();
    void setServerIP();
    void searchFinger(int place);
    String getDevID();
    String getPassword();
    String getIP();
    
  private:
    const char* ns    = "auth";           //namespace name; a memory buffer will open name auth
    const char* key1  = "password";      //key name
    const char* key2  = "ID";
    const char* key5  = "IpAdd";
    const String defaultPwd = "6748";  //default key value
};

extern Manager manager;
bool Input_Manager(int x, int y, int limit, const char* content, const String& mode, String& Uinput, String& star);
void admin(); //master of all functionality

#endif