#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define DELAY 30





int main() {
  // set all pins in PORTD as output
  DDRD = 0xFF;

  while (1) {
    // Blink LED from right to left
    for (uint8_t i = 0; i < 7; i++) {
      PORTD = (1 << i);               // Blink only the ith pin
      _delay_ms(DELAY);
    }

    // Blink LED from left to right
    for (uint8_t i = 7; i > 0; i--) {
      PORTD = (1 << i);
      _delay_ms(DELAY);
    }
  }

  return 0;
}
