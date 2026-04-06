#include "esp32-hal.h"
#include "HardwareSerial.h"
#include"FingerPrint_Config.h"

HardwareSerial fingerPrintSerial(1);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrintSerial);
// TaskHandle_t SensorTaskHandle = NULL;
float fingerTimer = 0;
bool  fingerPressed = false;

void Sensor_Config(){
  Serial.print("Enrollment Process......");
  fingerPrintSerial.begin(57600, SERIAL_8N1, RX2, TX2);

  Serial.print("Searching Fingerprint Sensor...");
  
  while(1){
    if(finger.verifyPassword()){
      Serial.print("OK\n");
      break;
    }else{
      Serial.print(".");
    }
  }
  //Printing all parameters of the sensor
  Serial.println("\nReading Sensor Parameters");
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0X")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);
  //Stored templates number
  finger.getTemplateCount();
  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
}

uint8_t getFingerprintEnroll(uint16_t id){

  Serial.println("Ready to enroll a fingerprint!");
  Serial.println("Please type in the ID # (from 1 to 999) you want to save this finger as...");
  Serial.print("Enrolling ID #"); Serial.println(id);

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while(p != FINGERPRINT_OK){
    DisplayImage(0, 0, 64, 128, fingerprint_icon);
    p = finger.getImage();
    switch(p){
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK First Attempt!

  p = finger.image2Tz(1);
  switch(p){
    case FINGERPRINT_OK:
      Serial.println("Image converted to template");
      DisplayImage(0, 0, 64, 128, fingerprint_OKicon);
      previousMillis = millis();
      denied = true;
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK First Image converted to template

  Serial.println("Remove finger");
  p=0;
  while(p != FINGERPRINT_NOFINGER) p = finger.getImage();
  Serial.print("ID #"); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while(p != FINGERPRINT_OK){
    if(denied && millis() - previousMillis >= 2000){
      DisplayText(0, 0, 1, 1, "");
      denied = false;
    }
    DisplayImage(0, 0, 64, 128, fingerprint_icon);
    p = finger.getImage();
    switch(p){
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  //OK Second Attempt

  p = finger.image2Tz(2);
  switch(p){
    case FINGERPRINT_OK:
      Serial.println("Image converted to template");
      DisplayImage(0, 0, 64, 128, fingerprint_OKicon);
      previousMillis = millis();
      denied = true;
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image to messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  //Ok Second Image converted to template

  Serial.print("Creating model for ID #"); Serial.println(id);

  p = finger.createModel();
  if( p == FINGERPRINT_OK){
    Serial.println("Fingerprint matched");
  }else if(p == FINGERPRINT_PACKETRECIEVEERR){
    Serial.println("Communication error");
    return p;
  }else if(p == FINGERPRINT_ENROLLMISMATCH){
    Serial.println("Fingerprint did not match");
    return p;
  }else{
    Serial.println("Unknown error");
    return p;
  }

  Serial.print("ID "); Serial.print(id);
  p = finger.storeModel(id);
  if(p == FINGERPRINT_OK){
    Serial.println("Stored!");
  }else if(p == FINGERPRINT_PACKETRECIEVEERR){
    Serial.println("Communication error");
    return p;
  }else if(p == FINGERPRINT_BADLOCATION){
    Serial.println("Could not store in thet location");
    return p;
  }else if(p == FINGERPRINT_FLASHERR){
    Serial.println("Error writing to flash");
    return p;
  }else{
    Serial.println("Unknown error");
    return p;
  }

  return true;

}

uint8_t getFingerprintID(int place){

  int p = -1;
  
  if(place){
    Serial.println("Waiting for valid finger to match");
    while(p != FINGERPRINT_OK){
      p = finger.getImage();
      switch(p){
        case FINGERPRINT_OK:
          Serial.println("Image taken");
          break;
        case FINGERPRINT_NOFINGER:
          Serial.print(".");
          break;
        case FINGERPRINT_PACKETRECIEVEERR:
          Serial.println("Communication error");
          break;
        case FINGERPRINT_IMAGEFAIL:
          Serial.println("Imaging error");
          break;
        default:
          Serial.println("Unknown error");
          break;
      }
    }
  }else{
    // uint32_t start = millis();
    // while(millis() - start < 100){
      p = finger.getImage();
      // while(p != FINGERPRINT_NOFINGER) p = finger.getImage();
      // p = finger.getImage();
      switch(p){
        case FINGERPRINT_OK:
          Serial.println("Image taken");
          break;
        case FINGERPRINT_NOFINGER:
          return p;
        case FINGERPRINT_PACKETRECIEVEERR:
          Serial.println("Communication error");
          return -1;
        case FINGERPRINT_IMAGEFAIL:
          Serial.println("Imaging error");
          return -1;
        default:
          Serial.println("Unknown error");
          return -1;
      }
    //}
  }

  // OK Image is captured

  p = finger.image2Tz();
  switch(p){
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      // vTaskSuspend(DisplayTaskHandle);
      DisplayImage(0, 0, 64, 128, fingerprint_OKicon);
      previousMillis = millis();
      denied = true;
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      fingerTimer = millis();
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      fingerTimer = millis();
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      fingerTimer = millis();
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      fingerTimer = millis();
      return p;
    default:
      Serial.println("Unknown error");
      fingerTimer = millis();
      return p;
  }

  // OK fingerprint is converted to template

  p = finger.fingerSearch();
  if(p == FINGERPRINT_OK){
    Serial.println("Found a print match!");
  }else if(p == FINGERPRINT_PACKETRECIEVEERR){
    Serial.println("Communication error");
    fingerTimer = millis();
    return p;
  }else if(p == FINGERPRINT_NOTFOUND){
    Serial.println("Did not find a match");
    fingerTimer = millis();
    return p;
  }else{
    Serial.println("Unknown error");
    fingerTimer = millis();
    return p;
  }

  // found a match!

  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  fingerTimer = millis();
  return true;
}

uint8_t delete_template(uint16_t id){

  uint8_t p = -1;

  p = finger.deleteModel(id);

  if(p == FINGERPRINT_OK){
    Serial.println("Deleted!");
    return true;
  }else if(p == FINGERPRINT_PACKETRECIEVEERR){
    Serial.println("Communication error");
  }else if(p == FINGERPRINT_BADLOCATION){
    Serial.println("Could not delete in that location");
  }else if(p == FINGERPRINT_FLASHERR){
    Serial.println("Error writing to flash");
  }else{
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
  }
  return p;

}

void empty_database(void){

  finger.emptyDatabase();
  Serial.println("Now database is empty");
  
}

void password_change(void){

  Serial.println("Set Password.....");
  uint8_t p = finger.setPassword(6748);
  if(p == FINGERPRINT_OK){
    Serial.println("Password Changed");
  }else{
    Serial.println("Something went to wrong");
  }

}
