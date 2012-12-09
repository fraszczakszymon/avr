#pragma once

#include <avr/io.h>

#define MODE_MFN  50
#define MODE_FN   100
#define MODE_DFN  150
#define MODE_SN   200
#define MODE_DSN  250
#define MODE_ADD  300
#define MODE_SUB  400
#define MODE_MUL  500
#define MODE_DIV  600

int isKeyboardPushed();
int detectKey(int);
void pushedKey(int);
void pushedNumber(int);
void setDotMode();
void calculateResult();
void changeMode(int);
void display();