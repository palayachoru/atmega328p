#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define DELAYTIME 50                                              /* ms */



uint8_t star_1up[] = {
  0b10000100,
  0b01101100,
  0b01111110,
  0b00011111,
  0b01111110,
  0b01101100,
  0b10000100,
  0b00000000,
  0b00000000,
  0b00000000,
  0b10000010,
  0b11111111,
  0b11111111,
  0b10000000,
  0b00000000,
  0b00000000,
  0b01111111,
  0b11111111,
  0b10000000,
  0b11111111,
  0b01111111,
  0b00000000,
  0b00000000,
  0b11111111,
  0b11111111,
  0b00110011,
  0b00110011,
  0b00011110,
  0b00011110,
};


int main(void) {
  DDRD = 0xff;   // set all pins in PORTD as output

  while (1) {
    for (uint8_t i = 0; i < sizeof(star_1up); i++) {
      PORTD = star_1up[i];
      _delay_ms(DELAYTIME);
    }

    PORTD = 0;     // turn of all LED: end of pattern
    _delay_ms(5 * DELAYTIME);
  }

  return 0;
}
