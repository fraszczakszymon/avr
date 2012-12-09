#include "calculator.h"
#include "lcd.h"
#include <avr/io.h> 

int MODE = MODE_FN;
double DATA[] = {0, 0};
int DATA_POS[] = {0, 0};

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
      changeMode(key);
      break;
    default:
      break;
  }
}

void pushedNumber(int key)
{
  switch (MODE)
  {
    case MODE_FN:
      if (DATA[0] == 0) {
        DATA[0] = (double) key;
      } else {
        DATA[0] = DATA[0]*10 + (double) key;
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

}

void changeMode(int key)
{

}

void display()
{
  char display[255] = {0};
  lcd_clrscr();
  lcd_home();
  sprintf(display, "%3.2f", DATA[0]);
  lcd_string(display);

}