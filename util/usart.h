#pragma once


#include <avr/io.h>

// setbaud.h need's F_CPU & BAUD to be defined
#ifndef F_CPU
  #define F_CPU 16000000UL
#endif

#ifndef BAUD
  #define BAUD 9600
#endif





void usart_init(void);

void transmit_byte(uint8_t data);

uint8_t receive_byte(void);
