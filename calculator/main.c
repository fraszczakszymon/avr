#include <avr/io.h>
#include "lcd.h"
#include "calculator.h"

int main(void)
{
  DDRB = 0x0F;
  int keyboardPushed = 0;
  int confirmed = 0;
  int col = 0;
  int key = -1;
  int keyboard[16] = {
     7,  8,  9, -6,
     4,  5,  6, -5,
     1,  2,  3, -4,
     0, -1, -2, -3
  };
  uint8_t columnIndexes[4] = {
    0b11111110,
    0b11111101,
    0b11111011,
    0b11110111
  };

  lcd_init();
  lcd_clrscr();
  lcd_home();

  while (1) {
    PORTB = columnIndexes[col];

    key = detectKey(col);
    keyboardPushed = isKeyboardPushed();

    if (keyboardPushed == 1 && confirmed == 0 && key != -1) {
      confirmed = 1;
      pushedKey(keyboard[key]);
    } else if (keyboardPushed == 0 && confirmed == 1) {
      confirmed = 0;
    }

    _delay_ms(25);
    if (keyboardPushed == 0 && ++col==4) {
      col=0;
    }
  }
}