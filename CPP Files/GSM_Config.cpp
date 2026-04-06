#include "esp32-hal.h"
#include "WString.h"
#include"GSM_Config.h"

HardwareSerial GSM_Serial(2);
String phnNum = "+88";
float GSMTimer = 0;
int prevRSSI = 0;

void GSM_Config(){
  GSM_Serial.begin(9600, SERIAL_8N1, RX1, TX1);
  GSM_Serial.println("AT");
  delay(500);
  printGSMresponse();
  GSM_Serial.println("AT+CMGF=1");
  delay(500);
  printGSMresponse();

  // while(1){
  //   if (Serial.available()) {
  //     String command = Serial.readStringUntil('\n');
  //     GSM_Serial.println(command);  // Send to GSM
  //   }

  //   // Send data from printGSMresponse() to Serial Monitor
  //   printGSMresponse();
  // }
}

void Send_SMS(String action, String name, String classNum, String section, String roll, String number){
  String smsContent = "";

  if(action == "Enrollment"){
    smsContent = "You have enrolled to the Biometric Attendance System";
    smsContent += "\nName: " + name +
                  "\nClass: " + classNum +
                  "\nSection: " + section +
                  "\nRoll: " + roll;
  }else if(action == "Delete"){
    smsContent = "You have been removed from Biometric Attendance System";
    smsContent += "\nName: " + name +
                  "\nClass: " + classNum +
                  "\nSection: " + section +
                  "\nRoll: " + roll;
  }else{
    smsContent = "Your Child has reached the School";
    smsContent += "\nName: " + name +
                  "\nClass: " + classNum +
                  "\nSection: " + section +
                  "\nRoll: " + roll;
  }

  GSM_Serial.println("AT+CMGF=1");
  printGSMresponse();
  delay(500);

  GSM_Serial.print("AT+CMGS=\"");
  phnNum += number;
  GSM_Serial.print(phnNum);
  GSM_Serial.println("\"");
  printGSMresponse();
  delay(500);

  GSM_Serial.print(smsContent);
  printGSMresponse();
  delay(500);

  GSM_Serial.write(26);
  printGSMresponse();
  delay(500);
  phnNum = "+88";
}

int getSignalStrength(){

  if(millis() - GSMTimer > 1000) {
    GSM_Serial.println("AT+CSQ"); 
    String GSMresponse = printGSMresponse();
    // Look for "+CSQ:"
    int index = GSMresponse.indexOf("+CSQ:");
    if (index != -1) {
      int commaIndex = GSMresponse.indexOf(",", index);
      if (commaIndex != -1) {
        String rssiStr = GSMresponse.substring(index + 6, commaIndex);
        int rssi = rssiStr.toInt();
        prevRSSI = rssi;
        GSMTimer = millis();
        return rssi; // Return raw RSSI value (0–31, 99 = unknown)
      }
    }
    GSMTimer = millis();
    return -1; // Error or not found
  }
  return prevRSSI;
}

String printGSMresponse(){

  String GSMresponse = "";
  while (GSM_Serial.available()) {
    char c = GSM_Serial.read();
    GSMresponse += c;
  }
  Serial.println(GSMresponse);
  Serial.println("----------------------");
  return GSMresponse;
}