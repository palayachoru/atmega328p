#include <avr/io.h>
#include <util/delay.h>



void pov_blink(uint8_t one_byte) {
  PORTD = one_byte;
  _delay_ms(10);
}


int main() {
  // set all pins in PORTD as output
  DDRD = 0xFF;

  while (1) {
    // pattern to enable lights
    pov_blink(0b00001110);
    pov_blink(0b00011000);
    pov_blink(0b10111101);
    pov_blink(0b01110110);

    pov_blink(0b00111100);
    pov_blink(0b00111100);
    pov_blink(0b00111100);

    pov_blink(0b01110110);
    pov_blink(0b10111101);
    pov_blink(0b00011000);
    pov_blink(0b00001110);

    // turn of all LED: end of pattern
    PORTD = 0;
    _delay_ms(200);
  }

  return 0;
}
