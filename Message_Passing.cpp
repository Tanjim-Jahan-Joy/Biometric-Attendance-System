#include <string.h>
#include "WString.h"
#include"Message_Passing.h"

HTTPClient http;

String postData;
String serverIP;
String endpoint = "/test_receiver.php";
String serverURL;
String serverRes[7];

void Send_Message(String UID, const char* action){
  serverURL = "http://" + (serverIP) + (endpoint);
  Serial.println(serverIP);
  Serial.println(serverURL);
  http.begin(serverURL);
  http.addHeader("Content-Type", "application/json");

  String jsonPayload = "{\"id\":\"" + UID + "\", \"action\":\"" + action + "\"}";

  Serial.println(jsonPayload);

  int httpCode = http.POST(jsonPayload);

  if(httpCode > 0){
    String response = http.getString();
    Serial.println("Response: "+response);
    // Allocate memory for JSON parsing
    const size_t capacity = JSON_OBJECT_SIZE(6) + 200;
    DynamicJsonDocument doc(capacity);

    // Parse JSON
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print(F("JSON parse failed: "));
      Serial.println(error.f_str());
      http.end();
      jsonPayload.clear();

      serverRes[0] = "Failed";
      serverRes[1] = "Invalid JSON";
    }

    // Extract "serverRes" & "status"
    String temp = doc["status"].as<String>();

    if(temp == "Failed"){
      serverRes[0] = doc["status"].as<String>();
      serverRes[1] = doc["message"].as<String>();
      Serial.println(serverRes[0]);
      Serial.println(serverRes[1]);

      http.end();
      jsonPayload.clear();
    }else if(temp == "Successful"){
      serverRes[0] = doc["status"].as<String>();
      serverRes[1] = doc["message"].as<String>();
      serverRes[2] = doc["name"].as<String>();
      serverRes[3] = String(doc["class"].as<int>());
      serverRes[4] = doc["section"].as<String>();
      serverRes[5] = String(doc["roll"].as<int>());
      serverRes[6] = doc["phoneNum"].as<String>();
      
      http.end();
      jsonPayload.clear();
    }
  }else{
    Serial.println("Failed to send POST:" +String(httpCode));
    http.end();
    jsonPayload.clear();
    serverRes[0] = "Failed";
    serverRes[1] = "Failed to send POST\ncheck server IP";
  }
}
