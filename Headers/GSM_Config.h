#ifndef GSM_H
#define GSM_H

#include<Arduino.h>
#include<Wire.h>

#define TX1 17   // Connect the 3V3RX pin of SIM900A to GPIO 17 of ESP32
#define RX1 16  // Connect the 3V3TX pin of SIM900A to GPIO 16 of ESP32

extern String phnNum;
extern float GSMTimer;
extern int prevRSSI;

void GSM_Config();
void Send_SMS(String action, String name, String classNum, String section, String roll, String number);
String printGSMresponse();
int getSignalStrength();

#endif