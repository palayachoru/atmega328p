#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define DELAYTIME 50



uint8_t invader1[] = {
  0b01110000,
  0b00011000,
  0b11111101,
  0b10110110,
  0b00111100,
  0b00111100,
  0b00111100,
  0b10110110,
  0b11111101,
  0b00011000,
  0b01110000
};

uint8_t invader2[] = {
  0b00001110,
  0b00011000,
  0b10111101,
  0b01110110,
  0b00111100,
  0b00111100,
  0b00111100,
  0b01110110,
  0b10111101,
  0b00011000,
  0b00001110
};


void pause(uint8_t iter) {
  for (uint8_t i = 0; i < iter; i++) _delay_ms(DELAYTIME);
}


void pov_blink(uint8_t arr[], uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    PORTD = arr[i];
    _delay_ms(DELAYTIME);
  }
  pause(5);
}



int main() {
  // set all pins in PORTD as output
  DDRD = 0xFF;

  while (1) {
    pov_blink(invader1, sizeof(invader1));
    pov_blink(invader2, sizeof(invader2));
  }

  return 0;
}
