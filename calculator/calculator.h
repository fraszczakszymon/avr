#pragma once

#include <avr/io.h>

#define DATA_MODE_FIRST_NUMBER    1
#define DATA_MODE_SECOND_NUMBER   2
#define DATA_MODE_RESULT          3

#define MODE_ADDITION             43
#define MODE_SUBTRACTION          45
#define MODE_MULTIPLICATION       42
#define MODE_DIVISION             47

int isKeyboardPushed();
int detectKey(int);
double calculateValue(int);
void pushedKey(int);
void pushNumber(int);
void setDotMode();
void setNumber(int, int);
void changeMode(int);
void calculateResult();
void display();