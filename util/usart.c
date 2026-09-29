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
 * TRANSMITTING DATA:
 * UCSR0A (USART Control and Status Register 0 A): contains status flags aboutthe UART hardware
 * UDRE0 (USART Data Register Empty): the hardware automatically sets 'UDRE0' bit
 *    to 1 when the transmission buffer (UDR0) becomes empty and is ready to receive new data.
 *
 * The Loop -- loop_until_bit_is_set():
 *  - This macro creates a while loop that continuously checks this bit.
 *  - If the bit is 0 (meaning the hardware is still busy transmitting the
 *     previous byte),the code pauses and waits.
 *  - The moment it becomes 1, the loop breaks, allowing the code to proceed
 *
 * UDR0 (USART Data Register 0): When you write your 8-bit data into this register,
 *   the hardware immediately clears the UDRE0 bit back to 0 (because the register is no longer empty)
 *
 * The Transmission:
 *  - the internal ATmega328P circuitry automatically takes over.
 *  - It moves the byte from UDR0 into a shift register, formats it with a start bit,
 *       parity bit (if used), and stop bits, and streams it out sequentially
 *       through the physical TX pin.
 */
void transmit_byte(uint8_t data) {
  loop_until_bit_is_set(UCSR0A, UDRE0);

  UDR0 = data;
}



/**
 * RECEIVING DATA:
 * RXC0 (USART Receive Complete): When the RX line is idle or a byte is still in
 *        the middle of being received, RXC0 is 0
 *
 * - The ATmega328P internal circuitry automatically samples the incoming physical
 *    RX pin. Once it successfully counts and shifts in all the bits of a full byte
 *    (including the start and stop bits), it moves that finished byte into
 *    the UDR0 receive buffer.
 * - The exact moment that byte lands in UDR0, the hardware automatically sets
 *    RXC0 to 1. This breaks the macro loop
 *
 * - return UDR0: reads the data from the register
 * - the act of reading the UDR0 register automatically clears the RXC0 bit back
 *    to 0 (provided there are no more unread bytes waiting in the hardware's internal receive buffer).
 */
uint8_t receive_byte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);

  return UDR0;
}


/**
 * Both transmit and receive functions use UDR0
 * Even though they share the exact same name in your code, they physically point
 *  to two different internal hardware registers inside the microcontroller:
 *
 *   - When you write to UDR0, the hardware routes the data to the Transmit Data Buffer
 *   - When you read from UDR0, the hardware routes data from the Receive Data Buffer
 *
 * This clever design saves register address space while keeping transmission
 *  and reception completely independent.
 */



void transmit_string(const char string[]) {
  for (uint8_t i = 0; string[i]; i++) {
    transmit_byte(string[i]);
  }
}
