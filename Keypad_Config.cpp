#include"Keypad_Config.h"

float buttonTimer  = 0;
bool buttonPressed = false; 

void KeyPad_Config(){
  Wire1.begin(keySDA, keySCL, 400000L);
  Serial.println("PCF8574 With Keypad");
}

String Read_Key(){
  // Simple Button Debouce
  if(buttonPressed){
    if(millis() - buttonTimer > 300){
      buttonTimer = millis();
      buttonPressed = false;
    }else{
      // return "empty";
    } // Do Nothing
  }else{
    Wire1.beginTransmission(0x20);
    Wire1.write(B11111110);
    Wire1.endTransmission();
    Wire1.requestFrom(0x20, 1);
    //238, 222, 190, 126
    switch(Wire1.read()){
      case 238:
        // Serial.println("1");
        buttonPressed = true;
        return "1";
        break;
      case 222:
        // Serial.println("2");
        buttonPressed = true;
        return "2";
        break;
      case 190:
        // Serial.println("3");
        buttonPressed = true;
        return "3";
        break;
      case 126:
        // Serial.println("A");
        buttonPressed = true;
        return "A";
        break;
    }

    Wire1.beginTransmission(0x20);
    Wire1.write(B11111101);
    Wire1.endTransmission();
    Wire1.requestFrom(0x20, 1);
    //237, 221, 189, 125
    switch(Wire1.read()){
      case 237:
        // Serial.println("4");
        buttonPressed = true;
        return "4";
        break;
      case 221:
        // Serial.println("5");
        buttonPressed = true;
        return "5";
        break;
      case 189:
        // Serial.println("6");
        buttonPressed = true;
        return "6";
        break;
      case 125:
        // Serial.println("B");
        buttonPressed = true;
        return "B";
        break;
    }

    Wire1.beginTransmission(0x20);
    Wire1.write(B11111011);
    Wire1.endTransmission();
    Wire1.requestFrom(0x20, 1);
    //235, 219, 187, 123
    switch(Wire1.read()){
      case 235:
        // Serial.println("7");
        buttonPressed = true;
        return "7";
        break;
      case 219:
        // Serial.println("8");
        buttonPressed = true;
        return "8";
        break;
      case 187:
        // Serial.println("9");
        buttonPressed = true;
        return "9";
        break;
      case 123:
        // Serial.println("C");
        buttonPressed = true;
        return "C";
        break;
    }

    Wire1.beginTransmission(0x20);
    Wire1.write(B11110111);
    Wire1.endTransmission();
    Wire1.requestFrom(0x20, 1);
    //231, 215, 183, 119
    switch(Wire1.read()){
      case 231:
        // Serial.println("*");
        buttonPressed = true;
        return "*";
        break;
      case 215:
        // Serial.println("0");
        buttonPressed = true;
        return "0";
        break;
      case 183:
        // Serial.println("#");
        buttonPressed = true;
        return "#";
        break;
      case 119:
        // Serial.println("D");
        buttonPressed = true;
        return "D";
        break;
    }
    buttonTimer = millis();
  }
  return "empty";
}