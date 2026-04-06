#ifndef OLED_H
#define OLED_H

#include<Arduino.h>
#include<SPI.h>
#include<Wire.h>
#include"NTP_Config.h"

// #include<U8g2lib.h>          // Universal Graphics Library Support both SSD1306, SH1106 OLED
#include<Adafruit_GFX.h>       // Adafruit Graphics Library 
#include<Adafruit_SH110X.h>   // #include<Adafruit_SD1306.h> library can be used for OLED model SD1306

#define oled_address 0x3c    // default I2C address of the OLED
#define SCREEN_WIDTH 128    // OLED Display width, in pixels
#define SCREEN_HEIGHT 64   // OLED Display height, in pixels 
#define OLED_RESET -1     // No reset pin is added

extern Adafruit_SH1106G OLED;
// extern TaskHandle_t DisplayTaskHandle;

extern const uint8_t wifi[];
extern const uint8_t NOwifi[];
extern const uint8_t logo[1024];
extern const uint8_t fingerprint_icon[1024];
extern const uint8_t fingerprint_OKicon[1025];
extern const uint8_t errorIcon[];
extern const uint8_t okIcon[];

extern bool denied;
extern bool show;
extern bool clc;
extern String errorMsg;
extern bool errorSign;
extern unsigned long lastScrollTime;
extern const int scrollDelay;  // in milliseconds
extern int scrollOffset;

void OLED_Config();
void DisplayDateTime(String DeviceID, const uint8_t* image, int life, int level);
void DisplayRec(int life);
void DisplayImage(int x, int y, int h, int w, const uint8_t* image);
void DisplayText(int x, int y, float size, bool flag, const char* text);
void DisplayScrollingText(char* menu[], const int numLines);

#endif