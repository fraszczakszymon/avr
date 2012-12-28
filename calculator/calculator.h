#pragma once

#include <avr/io.h>

#define DATA_MODE_FIRST_NUMBER    0
#define DATA_MODE_SECOND_NUMBER   1
#define DATA_MODE_RESULT          2

#define MODE_ADDITION             43
#define MODE_SUBTRACTION          45
#define MODE_MULTIPLICATION       42
#define MODE_DIVISION             47

int isKeyboardPushed();
int getKeyIndex(int);
void keyHandler(int);
double calculateValue(int);
void setValue(int, int);
void changeMode(int);
void calculateResult();
void displayValues();