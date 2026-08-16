/**
 * HOW TO BLINK A LED?
 *
 * 1. Enable the Pin as output Pin via DDRx register
 * 2. Set the Pin as high via PORTx register
 * 3. Add sleep
 * 4. Set the Pin as Low via PORTx register
 * 6. Add sleep
 *
 * x - corresponds to the Port(Bank) the pin resides
 *
 * NOTE: PB5 (Pin 5 in PORT B) - connected to builtin LED in Arduino Board
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // set Pin 5 as output pin (DDRB = 0b0001 0000)
  DDRB = DDRB | (1 << DDB5);

  while (1) {
    // set pin5 to high (PORTB | 0b0001 0000)
    PORTB = PORTB | (1 << DDB5);
    _delay_ms(500);               // wait sometime with pin state as high

    // set Pin5 to low (PORTB & 0b1110 1111)
    PORTB = PORTB & ~(1 << DDB5);
    _delay_ms(500);              // wait sometime with pin state as low
  }
}
