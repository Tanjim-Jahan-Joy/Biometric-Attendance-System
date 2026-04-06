#ifndef DATE_TIME_H
#define DATE_TIME_H

#include<Arduino.h>
#include<time.h>
#include<ESP32Time.h>
#include"OLED_Config.h"

extern const char* ntpServer;
extern const long gmtOffset_sec;
extern const int daylightOffset_sec;

extern struct tm timeInfo;
// extern char timeBuffer_1[50];
// extern char timeBuffer_2[50];
extern String currTime;
extern String currDate;

void ntp_config();
void CallDateTime();

#endif