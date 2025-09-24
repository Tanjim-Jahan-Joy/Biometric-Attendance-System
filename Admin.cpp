#include "HardwareSerial.h"
#include"Admin.h"

// TaskHandle_t AdminTaskHandle = NULL;
Preferences preferences;
Manager manager;
bool check = false;
String defaultPwd = "6748";
String key;
String Uinput;
String star;
String DeviceID;
String Password;
String UID;
unsigned long previousMillis = 0;
const unsigned long interval = 500;

char* menu[] = {
  "Enrollment Process",
  "Delete Fingerprint ID\n",
  "Get Fingerprint ID",
  "Empty Database",
  "Set Device Password",
  "Get Device Password",
  "Set Device ID",
  "Config IP Address",
  "Config WiFi"
};

bool Input_Manager(int x, int y, int limit, const char* content, const String& mode, String& Uinput, String& star){

  key = Read_Key();
  if(key != "empty"){
    if(key !="D" && key != "#" && key != "*"){
      if(Uinput.length() < limit){
        if(limit == -1 && key == "A"){
          Uinput = Uinput + ".";
        }else{
          Uinput = Uinput + key;
        }
        if(mode == "id"){
          if(limit == -1){
            DisplayText(10, 30, 1, 0, Uinput.c_str());
          }else{
            DisplayText(55, 30, 1, 0, Uinput.c_str());
          }
        }else if(mode == "pass"){
          star = star + "*";
          if(limit == -1){
            DisplayText(10, 30, 1, 0, star.c_str());
          }else{
            DisplayText(55, 30, 1, 0, star.c_str());
          }
        }
        // Serial.println(Uinput.length());
      }else{
        DisplayText(64, 45, 1, 0, "!");
        // Serial.println(Uinput.length());
      }
    }else if(key == "D" && !Uinput.isEmpty()){// D stands for delete
      Uinput = Uinput.substring(0, Uinput.length()-1);// remove the last character
      DisplayText(x, y, 1, 1, content);
      if(mode == "id"){
        if(limit == -1){
          DisplayText(10, 30, 1, 0, Uinput.c_str());
        }else{
          DisplayText(55, 30, 1, 0, Uinput.c_str());
        }
      }else if(mode == "pass"){
        star = star.substring(0, star.length()-1);
        if(limit == -1){
          DisplayText(10, 30, 1, 0, star.c_str());
        }else{
          DisplayText(55, 30, 1, 0, star.c_str());
        }
      }
      // Serial.println(Uinput.length());
    }else if(key == "#"){//# stands for enter
      if(limit == -1){
        return true;
      }else if(Uinput.length() == limit){
        return true;
      }
    }else{//* stands for exit from the function

    }
  }
  return false;
}

void admin(){

  if(denied && millis() - previousMillis >= 2000){
    // vTaskResume(DisplayTaskHandle);
    denied = false;
    DisplayText(0, 0, 1, 1, "");
  }

  if(!errorMsg.isEmpty() && !denied){

    if(errorSign) DisplayImage(41, 26, 40, 45, okIcon);
    else DisplayImage(41, 26, 40, 45, errorIcon);

    DisplayText(0, 0, 1, 0, errorMsg.c_str());
    previousMillis = millis();
    denied = true;
    errorMsg.clear();
  }

  if(!check){
    if(key == "*"){
      Uinput.clear(); star.clear(); check = false; key.clear();
      return;
    }
    check = Input_Manager(0, 0, 4, "", "pass", Uinput, star);
  }else{
    if(Uinput == Password){
      // vTaskSuspend(DisplayTaskHandle);
      const int numMenuItems = sizeof(menu) / sizeof(menu[0]);
      // const int numMenuItems = sizeof(ssidlist) / sizeof(ssidlist[0]);
      Uinput = "";
      star   = "";
      while(1){

        if(denied && millis() - previousMillis >= 2000){
          denied = false;
          DisplayText(0, 0, 1, 1, "");
        }

        if(!errorMsg.isEmpty() && !denied){
          if(errorSign) DisplayImage(41, 26, 40, 45, okIcon);
          else DisplayImage(41, 26, 40, 45, errorIcon);

          DisplayText(0, 0, 1, 0, errorMsg.c_str());
          previousMillis = millis();
          denied = true;
          errorMsg.clear();
        }

        DisplayScrollingText(menu, numMenuItems);
        key = Read_Key();
        if(key == "1"){// Start Enrollment Process
          UID += DeviceID;
          while(key != "*"){
            
            finger.getTemplateCount();
            String StrID = String(finger.templateCount + 1); String newID;
            if(StrID.length() == 1){
              newID = "00"; newID += StrID;
            }else if(StrID.length() == 2){
              newID = "0"; newID += StrID;
            }else {newID = StrID;}
            UID += newID;

            if(key != "*" && !denied){
              DisplayText(0, 0, 1, 1, "Enter Class:");
            }
            while(key != "*"){

              if(denied && millis() - previousMillis >= 2000){
                denied = false;
                DisplayText(0, 0, 1, 1, "");
              }

              if(!serverRes[1].isEmpty() && !denied){

                if(errorSign) DisplayImage(41, 26, 40, 45, okIcon);
                else DisplayImage(41, 26, 40, 45, errorIcon);

                DisplayText(0, 5, 1, 0, serverRes[1].c_str());
                previousMillis = millis();
                denied = true;
                serverRes[1].clear();
              }

              if(!errorMsg.isEmpty() && !denied){

                if(errorSign) DisplayImage(41, 26, 40, 45, okIcon);
                else DisplayImage(41, 26, 40, 45, errorIcon);

                DisplayText(0, 0, 1, 0, errorMsg.c_str());
                previousMillis = millis();
                denied = true;
                errorMsg.clear();
              }

              if(!denied){
                DisplayText(0, 0, 1, 0, "Enter Class:");
              }
              if(Input_Manager(0, 0, 2, "Enter Class:", "id", Uinput, star)){
                UID += Uinput;
                Serial.println(Uinput);
                Uinput.clear(); star.clear();
                break;
              }
            }

            if(key != "*"){
              DisplayText(0, 0, 1, 1, "Enter Section:");
            }
            while(key != "*"){
              if(Input_Manager(0, 0, 2, "Enter Section:", "id", Uinput, star)){
                UID += Uinput;
                Serial.println(Uinput);
                Uinput.clear(); star.clear();
                break;
              }
            }

            if(key != "*"){
              DisplayText(0, 0, 1, 1, "Enter Roll:");
            }
            while(key != "*"){
              if(Input_Manager(0, 0, 3, "Enter Roll:", "id", Uinput, star)){
                UID += Uinput;
                Serial.println(UID);
                if(getFingerprintEnroll(finger.templateCount + 1) == true){// call getFingerprintEnroll() for enrollment
                  Send_Message(UID, "Enrollment");
                  if(serverRes[0] == "Failed"){
                    Serial.println(serverRes[1]);
                    if(delete_template(finger.templateCount + 1)){
                      errorSign = false;
                      Serial.println("Template is deleted from local Storage");
                      errorMsg = "Template is deleted\nfrom local Storage";
                    }else{
                      errorSign = false;
                      Serial.println("Something Went Wrong");
                      errorMsg = "Something Went Wrong";
                    }
                  }else if(serverRes[0] == "Successful"){
                    errorSign = true;
                    Serial.println(serverRes[1]);
                    errorMsg = serverRes[1]; serverRes[1].clear();
                    Send_SMS("Enrollment", serverRes[2], serverRes[3], serverRes[4], serverRes[5], serverRes[6]);
                  }
                }else{
                  errorSign = false;
                  Serial.println("Something Went Wrong");
                  errorMsg = "Something Went Wrong";
                }
                break;
              }
            }
            Uinput.clear(); star.clear(); check = false; UID.clear();
            UID += DeviceID;
          }
          Uinput.clear(); star.clear(); UID.clear(); check = false;
          // DisplayText(0, 0, 1, 1, "");
          // break;
        }else if(key == "2"){// Delete a fingerprint ID
          UID += DeviceID;
          DisplayText(0, 0, 1, 1, "Enter Serial Number:");
          while(1){
            if(Input_Manager(0, 0, 3, "Enter Serial Number:", "id", Uinput, star)){
              UID += Uinput;
              Serial.println(Uinput.toInt());
              Serial.println(UID);
              Send_Message(UID, "Delete");
              if(serverRes[0] == "Successful"){
                if(delete_template(Uinput.toInt())){
                  Serial.println(serverRes[1]);
                  errorSign = true;
                  errorMsg  = serverRes[1].c_str(); serverRes[1].clear();
                  Send_SMS("Delete", serverRes[2], serverRes[3], serverRes[4], serverRes[5], serverRes[6]);
                }else{
                  Serial.println("Something went wrong");
                  errorMsg  = "Something went wrong";
                  errorSign = false;
                }
              }else if(serverRes[0] == "Failed"){
                Serial.println(serverRes[1]);
                errorMsg  = serverRes[1].c_str(); serverRes[1].clear();
                errorSign = false;
              }
              break;
            }
          }
          Uinput.clear(); star.clear(); check = false; UID.clear();
          // break;
        }else if(key == "3"){//Get Finger Print ID
          show = true;
          manager.searchFinger(1);
          show = false;
          Uinput.clear(); star.clear(); check = false;
          DisplayText(0, 0, 1, 1, "");
          // break;
        }else if(key == "4"){//Empty Database
          empty_database();
          DisplayText(0, 20, 1, 1, "The database has been emptied");
          previousMillis = millis();
          denied = true;
          Uinput.clear(); star.clear(); check = false;
          DisplayText(0, 0, 1, 1, "");
          // break;
        }else if(key == "5"){//Set Device Password
          manager.setPassword();
          Uinput.clear(); star.clear(); check = false;
          DisplayText(0, 0, 1, 1, "");
          // break;
        }else if(key == "6"){//Get Device Password
          String pass = manager.getPassword();
          while(key != "*"){
            key = Read_Key();
            DisplayText(55, 30, 1, 1, pass.c_str());
          }
          Uinput.clear(); star.clear(); check = false;
          DisplayText(0, 0, 1, 1, "");
          // break;
        }else if(key == "7"){//Set Device ID
          manager.setDevID();
          Uinput.clear(); star.clear(); check = false;
          DisplayText(0, 0, 1, 1, "");
          // break;
        }else if(key == "8"){//Config Server IP
          manager.setServerIP();
          Uinput.clear(); star.clear(); check = false;
          DisplayText(0, 0, 1, 1, "");
          // break;
        }else if(key == "9"){//Config WiFi Setting
          wifimanager.wifi_config(true);
          Uinput.clear(); star.clear(); check = false;
          DisplayText(0, 0, 1, 1, "");
          // break;
        }else if(key == "*"){//Forcefully Exit From Admin function
          Uinput.clear(); star.clear(); check = false;
          DisplayText(0, 0, 1, 1, "");
          break;
        }
      }
    }else if(!denied){
      // Serial.println("!!");
      DisplayText(25, 30, 1, 1, "Access Denied");
      previousMillis = millis();
      denied = true;
      Uinput.clear(); star.clear(); check = false;
    }
  }
  // vTaskResume(DisplayTaskHandle);
}

void Manager::searchFinger(int place){
  if(place){
    DisplayImage(0, 0, 64, 128, fingerprint_icon);
  }
  if(millis() - fingerTimer > 4000){
    int p = getFingerprintID(place);
    if(p == true){
      String StrID = String(finger.fingerID); String newID = DeviceID;
      if(StrID.length() == 1){
        newID += "00"; newID += StrID;
      }else if(StrID.length() == 2){
        newID += "0"; newID += StrID;
      }else{
        newID += StrID;
      }
      if(!place){
        Send_Message(newID, "Search");
        errorMsg = serverRes[1]; serverRes[1].clear();
        if(serverRes[0] == "Successful"){
          errorSign = true;
          Send_SMS("Search", serverRes[2], serverRes[3], serverRes[4], serverRes[5], serverRes[6]);
        }
      }
      if(place){
        while(key != "*"){
          if(denied && millis() - previousMillis >= 2000){
            // Serial.println("!");
            DisplayText(0, 0, 1, 1, "");
            denied = false;
          }
          key = Read_Key();
          DisplayText(55, 30, 1, 1, newID.c_str());
        }
      }
    }else if(p == FINGERPRINT_NOTFOUND){
      errorSign = false;
      errorMsg = "Need To Register";
    }else if(p == FINGERPRINT_NOFINGER){
      Serial.print(".");
    }else if(p == -1){
      Serial.print(".");
    }else{
      errorSign = false;
      errorMsg = "Something went wrong";
    }
  }
}

void Manager::begin(){
  // set default password & set initial device id
  preferences.begin(ns, false);
  if(!preferences.isKey(key1)){//the default password is set once in a lifetime
    preferences.putString(key1, defaultPwd);//this line will execute once after uploading the code
    preferences.end();
  }

  if(!preferences.isKey(key2)){
    while(1){
      if(Input_Manager(0, 10, 2, "Set Device ID:", "id", Uinput, star)){
        break;
      }
    }
    preferences.putString(key2, Uinput);
    preferences.end();
  }
  return;
}

void Manager::setServerIP(){
  String Uinput;
  String star;
  DisplayText(0, 10, 1, 1, "Set Server IP:");
  preferences.begin(ns, false);
  preferences.remove(key5);
  while(1){
    if(Input_Manager(0, 10, -1, "Set Server IP:", "id", Uinput, star)){
      break;
    }
  }
  Serial.println(serverIP);
  preferences.putString(key5, Uinput);
  preferences.end();
  ESP.restart();
  return;
}

void Manager::setPassword(){
  String Uinput = "";
  String star = "";
  DisplayText(0, 10, 1, 1, "Set Device Password:");
  preferences.begin(ns, false);
  preferences.remove(key1);
  while(1){
    if(Input_Manager(0, 10, 4, "Set Device Password:", "pass", Uinput, star)){
      break;
    }
  }
  preferences.putString(key1, Uinput);//change password
  preferences.end();
  ESP.restart();
  return;
}

//set device id execute once in a life time
void Manager::setDevID(){
  String Uinput = "";
  String star = "";
  DisplayText(0, 10, 1, 1, "Set Device ID:");
  preferences.begin(ns, false);
  preferences.remove(key2);
  while(1){
    if(Input_Manager(0, 10, 2, "Set Device ID:", "id", Uinput, star)){
      break;
    }
  }
  preferences.putString(key2, Uinput);
  preferences.end();
  ESP.restart();
  return;
}

String Manager::getDevID(){
  preferences.begin(ns, true);
  String id = preferences.getString(key2, "");//if any(default or new) password is not set then return default value
  Serial.println(id);
  preferences.end();
  return id; //if key is empty then return default value
}

//defaultPwd will never return since we are storing default password instantly after uploading code
//we are storing default password instantly after uploading code and key will never be empty
String Manager::getPassword(){
  preferences.begin(ns, true);
  String pwd = preferences.getString(key1, defaultPwd);//if any(default or new) password is not set then return default value
  Serial.println(pwd);
  preferences.end();
  return pwd; //if key is empty then return default value
}

String Manager::getIP(){
  preferences.begin(ns, true);
  String IP = preferences.getString(key5, "");
  Serial.println(IP);
  preferences.end();
  return IP;
}