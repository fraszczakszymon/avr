#include <avr/io.h>
#include "lcd.h"
#include "calculator.h"

int main(void)
{
  DDRB = 0x0F;
  int keyboardPushed = 0;
  int confirmed = 0;
  int col = 0;
  int keyIndex = -100;
  int keyboard[16] = {
     7,  8,  9, 47,
     4,  5,  6, 42,
     1,  2,  3, 45,
    -1,  0, -2, 43
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

    keyboardPushed = isKeyboardPushed();
    keyIndex = getKeyIndex(col);

    if (keyIndex == -100) {
      displayValues();
    }

    if (keyboardPushed == 1 && confirmed == 0 && keyIndex != -100) {
      confirmed = 1;
      keyHandler(keyboard[keyIndex]);
    } else if (keyboardPushed == 0 && confirmed == 1) {
      confirmed = 0;
    }

    _delay_ms(25);
    if (keyboardPushed == 0 && ++col==4) {
      col=0;
    }
  }
}