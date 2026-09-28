#include "usart.h"

#include <util/setbaud.h>  // setbaud.h need F_CPU & BAUD to be defined, so
                           // included after usart.h header

/**
* Initialization process consist of
*   1. Setting the baud rate
*   2. Setting frame format
*   3. Enabling transmitter/receiver depending on usage
*/
void usart_init(void) {
  // UBRR0L & UBRR0H - USART Baud Rate Register (12 bit register)
  // 0H: contain 4 most significant bits
  // 0L: contain 8 leat significant bits
  UBRR0H = UBRRH_VALUE;         // value defined in setbaud.h
  UBRR0L = UBRRL_VALUE;

  // UCSRnA - USART Control & Status Register A (8 bit register)
  #if USE_2X
    // Double the transmission speed (applicable to asynchronous only)
    UCSR0A |= (1 << U2X0);
  #else
    UCSR0A &= ~(1 << U2X0);
  #endif

  // UCSRnB - USART Control & Status Register B (8 bit register)
  // Receiver & Transmitter Enable
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);

  // UCSRnC - USART Control & Status Register C (8 bit register)
  // Frame Format - 8 bit character + 1 stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // set 8 bit character size
  UCSR0C &= ~(1 << USBS0);                 // USART Stop Bit Select; 0 = 1 stop bit, 1 = 2 stop bit
}


/**
 * For transmitting data
 *   1. Poll the flag value UDRE0 (USART Data Register Empty) in register UCSR0A
 *       this flag is set when transmit buffer is ready to transmit new data.
 *       NOTE: This value is READ-ONLY
 *   2. Write the data to UDR0 (USART I/O Data Register)
 */
void transmit_byte(uint8_t data) {
  loop_until_bit_is_set(UCSR0A, UDRE0);

  UDR0 = data;
}


/**
 * For receiving data
 *   1. poll the flag value RXC0 (USART Receive Complete) in register UCSR0A
 *       this flag is set when there are unread data in receive buffer and
 *       cleared when receive buffer is empty
 *   2. Read value from UDR0 (USART I/O Data Register)
 */
uint8_t receive_byte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);

  return UDR0;
}
