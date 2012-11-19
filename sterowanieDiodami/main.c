#include <avr/io.h>
#include <util/delay.h>               

int main(void)
{
  int status = 0;
  int activeLed = 0;
  DDRB = 0x03;
  PORTB = 0x01;
  DDRD = 0x00;
  PORTD = 0x07;

  while (1) {
    if (!(PIND & 0x02)) {
      PORTB ^= 0x01;
      PORTB ^= 0x02;
      _delay_ms(150);
    } else {
      if (PIND & 0x01) {
        status = 0;
        _delay_ms(50);
      } else {
        if (status == 0) {
          PORTB ^= 0x01;
          PORTB ^= 0x02;
          status = 1;
        }
        _delay_ms(50);
      }
    }

    if (!(PIND & 0x04) && (PIND & 0x02)) {
      if (PORTB & 0xFF) {
        activeLed = PORTB;
      }
      if (activeLed == 1) {
        PORTB ^= 0x01;
        _delay_ms(200);
      } else if (activeLed == 2) {
        PORTB ^= 0x02;
        _delay_ms(200);
      }
    }
  }
}