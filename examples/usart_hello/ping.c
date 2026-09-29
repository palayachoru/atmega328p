#include <util/delay.h>

#include "../../util/usart.h"


int main() {
  usart_init();

  while (1) {
    transmit_byte('A');   // continuouly sent 'A'
    _delay_ms(500);       // wait for half a second
  }

  return 0;
}
