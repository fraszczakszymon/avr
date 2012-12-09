#include "calculator.h"
#include "lcd.h"
#include <avr/io.h> 

int MODE = MODE_FN;
int DATA[] = {0, 0, 0};

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
      pushedNumber(key);
      break;
    case -1:
      setDotMode();
      break;
    case -2:
      calculateResult();
      break;
    case -3:
    case -4:
    case -5:
    case -6:
      if (DATA[1] == 0) {
        changeMode(key);
      } else {
        calculateResult();
      }
      break;
    default:
      break;
  }
  display();
}

void pushedNumber(int key)
{
  switch (MODE)
  {
    case MODE_MFN:
      if (DATA[0] == 0) {
        DATA[0] = -key;
      } else {
        DATA[0] = DATA[0]*10 - key;
      }
      break;
    case MODE_FN:
      if (DATA[0] == 0) {
        DATA[0] = key;
      } else {
        DATA[0] = DATA[0]*10 + key;
      }
      break;
    case MODE_ADD:
    case MODE_SUB:
    case MODE_MUL:
    case MODE_DIV:
      if (DATA[1] == 0) {
        DATA[1] = key;
      } else {
        DATA[1] = DATA[1]*10 + key;
      }
      break;
    default:
      break;
  }
}

void setDotMode()
{

}

void calculateResult()
{
  switch (MODE)
  {
    case MODE_ADD:
      DATA[2] = DATA[0] + DATA[1];
      break;
    case MODE_SUB:
      DATA[2] = DATA[0] - DATA[1];
      break;
    case MODE_MUL:
      DATA[2] = DATA[0] * DATA[1];
      break;
    case MODE_DIV:
      DATA[2] = DATA[0] / DATA[1];
      break;
  }
  MODE = MODE_RES;
}

void changeMode(int key)
{
  switch (key)
  {
    case -3:
      MODE = MODE_ADD;
      break;
    case -4:
      if (DATA[0] != 0) {
        MODE = MODE_SUB;
      } else {
        MODE = MODE_MFN;
      }
      break;
    case -5:
      MODE = MODE_MUL;
      break;
    case -6:
      MODE = MODE_DIV;
      break;
  }
}

void display()
{
  char line[16] = {0};
  lcd_clrscr();

  if (MODE != MODE_RES) {
    if (DATA[0] > 0) {
      lcd_gotoxy(0,0);
      sprintf(line, "%16d", DATA[0]);
      lcd_string(line);
    }
    if (DATA[1] > 0) {
      lcd_gotoxy(1,1);
      sprintf(line, "%15d", DATA[1]);
      lcd_string(line);
    }
  } else {
    lcd_gotoxy(1,1);
    sprintf(line, "%15d", DATA[2]);
    lcd_string(line);
  }

  if (MODE >= 200) {
    lcd_gotoxy(0,1);
    switch (MODE)
    {
      case MODE_ADD:
        sprintf(line, "+");
        break;
      case MODE_SUB:
        sprintf(line, "-");
        break;
      case MODE_MUL:
        sprintf(line, "*");
        break;
      case MODE_DIV:
        sprintf(line, "/");
        break;
      case MODE_RES:
        sprintf(line, "=");
        break;
    }
    lcd_string(line);
  }
}