#ifndef KEYPAD_H
#define KEYPAD_H

#include<Arduino.h>
#include<Wire.h>

#define keySDA 33
#define keySCL 32

extern float buttonTimer;
extern bool buttonPressed;

void KeyPad_Config();
String Read_Key();

#endif