#include "calculator.h"
#include <avr/io.h> 

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

int isKeyboardPushed() {
  return ((!(PINB & 0x10)) || (!(PINB & 0x20)) || (!(PINB & 0x40)) || (!(PINB & 0x80)));
}