#include <avr/io.h>
#include <util/delay.h>               

int main(void)
{
  int status = 0;
  DDRB  |= _BV(0)|_BV(1);
  PORTB |=  _BV(0);
  PORTB &= ~_BV(1);
  DDRD  &= ~_BV(0);
  PORTD |=  _BV(0);

  while (1) {
    if(PIND & _BV(0)) {
      status = 0;
      _delay_ms(50);
    } else {
      if (status == 0) {
        PORTB ^=_BV(0);
        PORTB ^=_BV(1);
        status = 1;
      }
      _delay_ms(50);
    }
  }
}