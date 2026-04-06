#include"NTP_Config.h"

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 21600;
const int daylightOffset_sec = 0;

struct tm timeInfo;
String currTime;
String currDate;

ESP32Time rtc(0);

void ntp_config(){
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); // Sending request to NTP server
  if(!getLocalTime(&timeInfo)){
    Serial.println("Failed to obtain time");
  }else{
    rtc.setTime(
      timeInfo.tm_sec,
      timeInfo.tm_min,
      timeInfo.tm_hour,
      timeInfo.tm_mday,
      timeInfo.tm_mon + 1,
      timeInfo.tm_year + 1900
    );
    //System.println(dateMatch);
  }
  // Serial.println(&timeInfo, "%H:%M:%S");
  // Serial.println(&timeInfo, "%A, %B %d, %Y");
  return;
}

void CallDateTime(){
  currTime = rtc.getTime();
  currDate = rtc.getDate();
  
  // timeInfo = rtc.getTimeStruct();
  // strftime(timeBuffer_1, sizeof(timeBuffer_1), "%H:%M:%S", &timeInfo);
  // strftime(timeBuffer_2, sizeof(timeBuffer_2), "%A, %B %d, %Y", &timeInfo);
  // Serial.println(timeBuffer_1);
  // Serial.println(timeBuffer_2);
  return;
}
