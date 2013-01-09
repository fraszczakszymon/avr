#include <avr/io.h>
#include "lcd.h"
#include "calculator.h"

int DATA_MODE = DATA_MODE_FIRST_NUMBER;
int MODE = 0;
int STATUS[] = {0, 0};
int SIGN = 1;
int DOT_DIVIDER = 0;
double VALUES[] = {0, 0, 0};

int isKeyboardPushed() {
  return ((!(PINB & 0x10)) || (!(PINB & 0x20)) || (!(PINB & 0x40)) || (!(PINB & 0x80)));
}

int getKeyIndex(int col)
{
  int row;

  if (!(PINB & 0x10)) {
    row = 0;
  } else if (!(PINB & 0x20)) {
    row = 1;
  } else if (!(PINB & 0x40)) {
    row = 2;
  } else if (!(PINB & 0x80)) {
    row = 3;
  } else {
    return -1;
  }

  return row*4 + col;
}

void keyHandler(int key)
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
        setValue(DATA_MODE, key);
      }
      break;
    case -1:
      if (DOT_DIVIDER == 0) {
        DOT_DIVIDER = 1;
      }
      break;
    case -2:
      if (STATUS[0] == 1 && STATUS[1] == 1) {
        calculateResult();
      }
      break;
    case 43:
    case 45:
    case 42:
    case 47:
      changeMode(key);
      break;
  }

  displayValues();
}

double calculateValue(int key)
{
  if (DOT_DIVIDER != 0 && DOT_DIVIDER < 10000) {
    DOT_DIVIDER *= 10;
    return SIGN * key / (double) DOT_DIVIDER;
  } else if (DOT_DIVIDER == 0) {
    return key*SIGN;
  }
  return 0;
}

void setValue(int valueIndex, int key)
{
  double pushedValue = calculateValue(key);

  if (STATUS[valueIndex] == 0) {
    VALUES[valueIndex] = pushedValue;
    STATUS[valueIndex] = 1;
  } else {
    if (DOT_DIVIDER == 0) {
      VALUES[valueIndex] = VALUES[valueIndex]*10 + pushedValue;
    } else {
      VALUES[valueIndex] = VALUES[valueIndex] + pushedValue;
    }
  }
}

void changeMode(int key)
{
  if (DATA_MODE != DATA_MODE_RESULT && STATUS[1] == 1) {
    calculateResult();
  }

  if (DATA_MODE == DATA_MODE_RESULT) {
    VALUES[0] = VALUES[2];
    VALUES[1] = 0;
    STATUS[1] = 0;
  }

  if (STATUS[0] == 1) {
    MODE = key;
    DATA_MODE = DATA_MODE_SECOND_NUMBER;
    DOT_DIVIDER = 0;
    SIGN = 1;
  } else if (key == MODE_SUBTRACTION) {
    SIGN = -1;
  }
}

void dividingByZeroAnimation()
{
  char line[16];
  int i;

  lcd_gotoxy(0, 0);
  sprintf(line, "Bledne dzialanie");
  lcd_string(line);

  lcd_clrline(1);
  for (i=0; i<16; i++) {
    lcd_gotoxy(i, 1);
    sprintf(line, ".");
    lcd_string(line);
    _delay_ms(100);
  }

  DATA_MODE = DATA_MODE_FIRST_NUMBER;
  MODE = 0;
  STATUS[0] = 0;
  STATUS[1] = 0;
  SIGN = 1;
  DOT_DIVIDER = 0;
  VALUES[0] = 0;
  VALUES[1] = 0;
  VALUES[2] = 0;
}

void calculateResult()
{
  switch (MODE) {
    case MODE_ADDITION:
      VALUES[2] = VALUES[0] + VALUES[1];
      break;
    case MODE_SUBTRACTION:
      VALUES[2] = VALUES[0] - VALUES[1];
      break;
    case MODE_MULTIPLICATION:
      VALUES[2] = VALUES[0] * VALUES[1];
      break;
    case MODE_DIVISION:
      if (VALUES[1] == 0) {
        dividingByZeroAnimation();
        return;
      }
      VALUES[2] = VALUES[0] / VALUES[1];
      break;
  }
  DATA_MODE = DATA_MODE_RESULT;
}

void displayValues()
{
  char line[16];

  if (DATA_MODE != DATA_MODE_RESULT) {
    lcd_gotoxy(0, 0);
    sprintf(line, " %15.7g", VALUES[0]);
    lcd_string(line);

    if (STATUS[1] == 1) {
      lcd_gotoxy(0, 1);
      sprintf(line, " %15.7g", VALUES[1]);
      lcd_string(line);
    } else {
      lcd_clrline(1);
    }
  } else {
    lcd_clrline(0);
    lcd_gotoxy(1, 1);
    sprintf(line, "%15.7g", VALUES[2]);
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