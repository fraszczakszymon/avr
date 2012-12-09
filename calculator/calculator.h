#pragma once

#include <avr/io.h>

#define MODE_MFN  50
#define MODE_FN   100
#define MODE_ADD  200
#define MODE_SUB  300
#define MODE_MUL  400
#define MODE_DIV  500
#define MODE_RES  600

int isKeyboardPushed();
int detectKey(int);
void pushedKey(int);
void pushedNumber(int);
void setDotMode();
void calculateResult();
void changeMode(int);
void display();