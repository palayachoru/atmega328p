# Configurations
MCU        = atmega328p
F_CPU      = 16000000UL
PORT       = /dev/ttyACM0
BAUD       = 115200
PROGRAMMER = stk500v1

USART_HEADER = -I../util
USART_SRC    = ../util/usart.c


# Generate the executable
hello.bin: hello.c
avr-gcc -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) $(USART_HEADER) -o hello.bin hello.c $(USART_SRC)

# Generate the hex file
hello.hex: hello.bin
	avr-objcopy -O ihex hello.bin hello.hex -j .text -j .data

# Using Arduino as flash programmer, write the code into chip's flash memory
flash: hello.hex
	avrdude -p $(MCU) \
	        -b $(BAUD) \
			-C /etc/avrdude.conf \
			-c $(PROGRAMMER) \
			-P $(PORT) \
			-U flash:w:hello.hex:i \
			-V -F -v -v

clean:
	rm -f *.bin *.hex


hex: hello.hex
