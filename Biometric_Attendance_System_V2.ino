#include"WiFi_Config.h"
#include"NTP_Config.h"
#include"OLED_Config.h"
#include"FingerPrint_Config.h"
#include"Keypad_Config.h"
#include"Admin.h"
#include"GSM_Config.h"

#define ANALOG_PIN 34        // GPIO 34
#define R1 213.0            // 213 ohm resistor (connected to input voltage)
#define R2 213.0           // 213 ohm resistor (connected to GND)

/*
void DisplayTask(void *para){
  for(;;){
    if(!Uinput.isEmpty() && !clc){
      DisplayText(0, 0, 1, 1, "");
      DisplayText(55, 30, 1, 0, star.c_str());
      clc = true;
    }
    if(Uinput.isEmpty()){
      CallDateTime();
      // DisplayRec(BatteryVol());
      if(WiFi.status() == WL_CONNECTED){
        // DisplayImage(0, 0, 21, 15, wifi);
        DisplayDateTime(DeviceID, wifi, BatteryVol(), getSignalStrength());
      }else DisplayDateTime(DeviceID, NOwifi, BatteryVol(), getSignalStrength()); //DisplayImage(0, 0, 21, 15, NOwifi);
      // DisplayDateTime(DeviceID);
      clc = false;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void AdminTask(void *para){
  for(;;){
    admin();
    // vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void SensorTask(void *para){
  for(;;){
    manager.searchFinger(0);
    // vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
*/

int BatteryVol(){
  int analogValue = analogRead(ANALOG_PIN);  // Read ADC value (0–4095)

  // Convert analog value to voltage at the divider output (Vout)
  float vout = (analogValue / 4095.0) * 3.3;

  // Calculate the actual input voltage (Vin) before the divider
  float vin = vout * ((R1 + R2) / R2);

  // Serial.print("Analog Value: ");
  // Serial.print(analogValue);
  // Serial.print(" | Vout: ");
  // Serial.print(vout, 2);
  // Serial.print(" V | Vin: ");
  // Serial.print(vin, 2);
  // Serial.println(" V");

  return (vin/5)*100;
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  analogReadResolution(12);
  OLED_Config();
  KeyPad_Config();
  // wifi_config("TP-Link_D3FF", "11608288");
  wifimanager.wifi_config(false);
  ntp_config();
  Sensor_Config();
  GSM_Config();
  manager.begin();
  DeviceID = manager.getDevID();
  Password = manager.getPassword();
  serverIP = manager.getIP();
  /*
  xTaskCreatePinnedToCore(DisplayTask, "DisplayTask", 2048, NULL, 1, &DisplayTaskHandle, 1);
  xTaskCreatePinnedToCore(SensorTask, "SensorTask", 4096, NULL, 1, &SensorTaskHandle, 1);
  xTaskCreatePinnedToCore(AdminTask, "AdminTask", 4096, NULL, 1, &AdminTaskHandle, 1);
  */
}

void loop(){
  admin();

  if(!Uinput.isEmpty() && !clc){
    DisplayText(0, 0, 1, 1, "");
    DisplayText(55, 30, 1, 0, star.c_str());
    clc = true;
  }
  if(Uinput.isEmpty()){
    CallDateTime();
    if(WiFi.status() == WL_CONNECTED){
      DisplayDateTime(DeviceID, wifi, BatteryVol(), getSignalStrength());
    }else DisplayDateTime(DeviceID, NOwifi, BatteryVol(), getSignalStrength());
    clc = false;
  }

  manager.searchFinger(0);
}