#include <avr/io.h>
#include "lcd.h"
#include "calculator.h"

int DATA_MODE = DATA_MODE_FIRST_NUMBER;
int MODE = 0;
int PUT[] = {0, 0};
int SIGN = 1;
int DOT_MODE = 0;
double DATA[] = {0, 0, 0};

int isKeyboardPushed() {
  return ((!(PINB & 0x10)) || (!(PINB & 0x20)) || (!(PINB & 0x40)) || (!(PINB & 0x80)));
}

int detectKey(int col)
{
  int row = -1;
  if (!(PINB & 0x10)) {
    row = 0;
  }
  if (!(PINB & 0x20)) {
    row = 1;
  }
  if (!(PINB & 0x40)) {
    row = 2;
  }
  if (!(PINB & 0x80)) {
    row = 3;
  }
  if (row == -1) {
    return -1;
  }

  return row*4 + col;
}

void pushedKey(int key)
{
  switch (key)
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      if (DATA_MODE != DATA_MODE_RESULT) {
        setNumber(DATA_MODE, key);
      }
      break;
    case -1:
      if (DOT_MODE == 0) {
        DOT_MODE = 1;
      }
      break;
    case -2:
      if (PUT[0] == 1 && PUT[1] == 1) {
        calculateResult();
      }
      break;
    case -3:
    case -4:
    case -5:
    case -6:
      changeMode(key);
      break;
  }
  display();
}

void setNumber(int number, int key)
{
  double pushedValue = calculateValue(key);

  if (PUT[number] == 0) {
    DATA[number] = pushedValue;
    PUT[number] = 1;
  } else {
    if (DOT_MODE == 0) {
      DATA[number] = DATA[number]*10 + pushedValue;
    } else {
      DATA[number] = DATA[number] + pushedValue;
    }
  }
}

double calculateValue(int key)
{
  if (DOT_MODE != 0 && DOT_MODE < 10000) {
    DOT_MODE *= 10;
    return SIGN * key / (double) DOT_MODE;
  } else if (DOT_MODE == 0) {
    return (double) key*SIGN;
  }
  return 0;
}

void changeMode(int key)
{
  if (DATA_MODE != DATA_MODE_RESULT && PUT[1] == 1) {
    calculateResult();
  }

  if (DATA_MODE == DATA_MODE_RESULT) {
    DATA[0] = DATA[2];
    DATA[1] = 0;
    PUT[1] = 0;
  }

  switch (key) {
    case -3:
      MODE = MODE_ADDITION;
      break;
    case -4:
      if (PUT[0] == 1) {
        MODE = MODE_SUBTRACTION;
      } else {
        SIGN = -1;
      }
      break;
    case -5:
      MODE = MODE_MULTIPLICATION;
      break;
    case -6:
      MODE = MODE_DIVISION;
      break;
  }
  if (PUT[0] == 1) {
    DATA_MODE = DATA_MODE_SECOND_NUMBER;
    DOT_MODE = 0;
    SIGN = 1;
  }
}

void calculateResult()
{
  switch (MODE) {
    case MODE_ADDITION:
      DATA[2] = DATA[0] + DATA[1];
      break;
    case MODE_SUBTRACTION:
      DATA[2] = DATA[0] - DATA[1];
      break;
    case MODE_MULTIPLICATION:
      DATA[2] = DATA[0] * DATA[1];
      break;
    case MODE_DIVISION:
      DATA[2] = DATA[0] / DATA[1];
      break;
  }
  DATA_MODE = DATA_MODE_RESULT;
}

void display()
{
  char line[16] = {0};

  if (DATA_MODE != DATA_MODE_RESULT) {
    if (PUT[0] == 1) {
      lcd_gotoxy(0, 0);
      sprintf(line, " %15.8g", DATA[0]);
      lcd_string(line);
    } else {
      lcd_clrline(0);
    }
    if (PUT[1] == 1) {
      lcd_gotoxy(0, 1);
      sprintf(line, " %15.8g", DATA[1]);
      lcd_string(line);
    } else {
      lcd_clrline(1);
    }
  } else {
    lcd_clrline(0);
    lcd_gotoxy(1, 1);
    sprintf(line, "%15.8g", DATA[2]);
    lcd_string(line);
  }

  lcd_gotoxy(0, 1);
  if (DATA_MODE == DATA_MODE_RESULT) {
    sprintf(line, "=");
    lcd_string(line);
  } else if (MODE != 0) {
    sprintf(line, "%c", MODE);
    lcd_string(line);
  }
}