#include"WiFi_Config.h"

// void wifi_config(const char* ssid, const char* password){
  // WiFi.begin(ssid, password);
  // Serial.print("Connecting to the wifi");
  // while(WiFi.status() != WL_CONNECTED){
  //   Serial.print(".");
  // }
  // Serial.println("\nWifi is connected");
  // return;
// }

char* ssidlist[10];
WiFiManager wifimanager;
bool wifiStatus = false;

void WiFiManager::wifi_config(bool frc){
  preferences.begin(net, true);
  if((!preferences.isKey(key3) && !preferences.isKey(key4)) || frc){
    preferences.end();
    String Uinput;
    String star;
    int index;

    while(!wifiStatus || frc){
      frc = false;
      errorMsg = "Scanning WiFi....";
      DisplayText(0, 25, 1, 1, "Scanning WiFi....");
      int n = WiFi.scanNetworks();
      WiFi.scanComplete();
      if(n == 0){
        DisplayText(10, 30, 1, 1, "No Networks Found....");
        previousMillis = millis();
        denied = true;
        
      }else{

        for(int i = 0; i < n && i < 10; ++i){

          String ssid = WiFi.SSID(i);
          ssidlist[i] = (char*)malloc(ssid.length() + 1);
          if(ssidlist[i] != nullptr){
            strcpy(ssidlist[i], ssid.c_str());
          }else{
            ssidlist[i] = (char*)"MemErr";
          }
        }
        const int itemCount = (n < 10) ? n : 10;
        // const int numMenuItems = sizeof(ssidlist) / sizeof(ssidlist[0]);
        while(1){

          Input_Manager(15, 5, 2, "Chose WiFi:", "id", Uinput, star);
          if(Uinput.isEmpty()){

            if(denied && millis() - previousMillis >= 2000){
              denied = false;
              DisplayText(0, 0, 1, 1, "");
            }
            if(!errorMsg.isEmpty() && !denied){

              DisplayText(0, 25, 1, 0, errorMsg.c_str());
              previousMillis = millis();
              denied = true;
              errorMsg.clear();
            }
            DisplayScrollingText(ssidlist, itemCount);
          }else{

            DisplayText(15, 5, 1, 1, "Chose WiFi:");
            DisplayText(55, 30, 1, 0, Uinput.c_str());
            while(1){

              if(Input_Manager(15, 5, 2, "Chose WiFi:", "id", Uinput, star)){
                index = Uinput.toInt();
                index = (index > 10) ? 1 : index;
                index = (index == 0) ? 1 : index;
                DisplayText(10, 0, 1, 1, ssidlist[index - 1]);
                Uinput.clear(); star.clear();
                break;
              }
            }
            while(1){

              if(Input_Manager(10, 0, -1, ssidlist[index - 1], "pass", Uinput, star)){
                WiFi.begin(ssidlist[index - 1], Uinput.c_str());
                Serial.print("Connecting to the wifi");
                DisplayText(0, 30, 1, 1, "Connecting to wifi...");
                previousMillis = millis();
                while(WiFi.status() != WL_CONNECTED){
                  if(millis() - previousMillis >= 3000){
                    DisplayText(0, 30, 1, 1, "Wrong Credentials");
                    previousMillis = millis();
                    denied = true;
                    Uinput.clear(); star.clear();
                    WiFi.disconnect(true); WiFi.scanDelete(); 
                    for (int i = 0; i < 10; i++) {
                      if (ssidlist[i] != nullptr && strcmp(ssidlist[i], "MemErr") != 0) {
                        free(ssidlist[i]);
                      }
                    }
                    break;
                  }
                  Serial.print(".");
                }
                if(WiFi.status() == WL_CONNECTED){
                  DisplayText(12, 30, 1, 1, "Wifi is connected");
                  previousMillis = millis();
                  denied = true;
                  preferences.begin(net, false);
                  preferences.remove(key3); preferences.remove(key4);
                  preferences.putString(key3, ssidlist[index - 1]);
                  preferences.putString(key4, Uinput);
                  preferences.end();
                  Uinput.clear(); star.clear();
                  Serial.println("\nWifi is connected");
                  for (int i = 0; i < 10; i++) {
                    if (ssidlist[i] != nullptr && strcmp(ssidlist[i], "MemErr") != 0) {
                      free(ssidlist[i]);
                    }
                  }
                  wifiStatus = true;
                  break;
                }
                break;
              }
            }
            break;
          }
        }
      }
    }
    return;
  }else{
    preferences.begin(net, true);
    String ssid = preferences.getString(key3, "");
    String pass = preferences.getString(key4, "");
    Serial.printf("%s %s", ssid, pass);
    preferences.end();
    WiFi.begin(ssid, pass);
    Serial.print("Connecting to the wifi");
    DisplayText(0, 30, 1, 1, "Connecting to wifi");
    previousMillis = millis();
    while(WiFi.status() != WL_CONNECTED){
      if(millis() - previousMillis >= 3000){
        DisplayText(0, 30, 1, 1, "Wrong Credentials");
        previousMillis = millis();
        denied = true;
        break;
      }
      Serial.print(".");
    }
    if(WiFi.status() == WL_CONNECTED){

      DisplayText(12, 30, 1, 1, "Wifi is connected");
      previousMillis = millis();
      denied = true;
      Serial.println("\nWifi is connected");
      wifiStatus = true;
    }
  }
}