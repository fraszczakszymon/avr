#include <avr/io.h>
#include "lcd.h"

int detectKey(int col)
{
  int row = 0;
  if (!(PINB & 0x10)) {
    row = 1;
  }
  if (!(PINB & 0x20)) {
    row = 2;
  }
  if (!(PINB & 0x40)) {
    row = 3;
  }
  if (!(PINB & 0x80)) {
    row = 4;
  }
  if (row == 0) {
    return 0;
  }

  return (row-1)*4 + col + 1;
}

int isKeyboardPushed() {
  if ((!(PINB & 0x10)) || (!(PINB & 0x20)) || (!(PINB & 0x40)) || (!(PINB & 0x80))) {
    return 1;
  }
  return 0;
}

int main(void)
{
  DDRB = 0x0F;
  int keyboardOutput[4] = {14, 13, 11, 7};
  int col=0, temp=0, key=0;
  char display[255] = {0};

  lcd_init();
  lcd_clrscr();
  lcd_home();

  while (1) {
    PORTB = keyboardOutput[col];

    temp = detectKey(col);
    if (isKeyboardPushed() == 1 && temp != key) {
      lcd_home();
      if (temp>0) {
        key = temp;
      }
      sprintf(display, "Klawisz: %d   ", key);
      lcd_string(display);
    }
    _delay_ms(25);

    if (++col==4) {
      col=0;
    }
  }
}