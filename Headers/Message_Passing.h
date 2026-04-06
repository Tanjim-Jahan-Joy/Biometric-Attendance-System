#ifndef MessagePassing_H
#define MessagePassing_H

#include<HTTPClient.h>
#include <ArduinoJson.h>
#include<Arduino.h>
#include"GSM_Config.h"

extern HTTPClient http;
// extern const char* serverIP;
// extern const char* endpoint;
extern String serverIP;
extern String endpoint;
extern String serverURL;
extern String postData;
extern String serverRes[7];
void Send_Message(String UID, const char* action);

#endif