#ifndef FingerPrint_H
#define FingerPrint_H

#include<Arduino.h>
#include<Wire.h>
#include<Adafruit_Fingerprint.h>
#include"OLED_Config.h"
#include"Admin.h"

#define TX2 04  // Connect the RX pin of FingerPrintSensor to GPIO 04
#define RX2 05 // Connect the TX pin of FingerPrintSensor to GPIO 05

extern HardwareSerial fingerPrintSerial;
extern Adafruit_Fingerprint finger;
// extern TaskHandle_t SensorTaskHandle;
extern float fingerTimer;
extern bool  fingerPressed;

void Sensor_Config();
uint8_t getFingerprintEnroll(uint16_t id);
uint8_t getFingerprintID(int place);
uint8_t delete_template(uint16_t id);
void empty_database(void);
void password_change(void);

#endif