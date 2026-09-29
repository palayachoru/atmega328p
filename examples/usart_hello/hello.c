#include "../../util/usart.h"

/* NOTE: to view this in computer: screen /dev/ttyACM0 9600 */

int main(void) {
  usart_init();

  // transmit this string
  const char data[] = "Hello World!! from ATMega";

  for (uint8_t i = 0; data[i]; i++) {
    // each char in string is 1 byte and transmit one byte per loop
    transmit_byte(data[i]);
  }

  return 0;
}
