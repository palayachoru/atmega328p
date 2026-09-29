#include "../../util/usart.h"


// NOTE: The character we type will not be printed in the terminal, it's send
// over the serial wire and microcontoller echos back, which got printed
// To prove this if we pass the received_byte + 1 to transmit byte, only the
// next character to what we type is printed not that character

int main() {
  usart_init();    // initialize usart

  uint8_t received_byte;

  while (1) {
    // recieve the character entered in the computer terminal
    received_byte = receive_byte();

    // transmit the next character back to the computer
    transmit_byte(received_byte + 1);
  }

  return 0;
}
