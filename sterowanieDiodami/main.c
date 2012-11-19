#include <avr/io.h>
#include <util/delay.h>               

int main(void)
{
  int status = 0;
  DDRB = 0x03;
  PORTB = 0x01;
  DDRD = 0x00;
  PORTD = 0x01;

  while (1) {
    if(PIND & 0x01) {
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
}