# Configurations
MCU        = atmega328p
F_CPU      = 16000000UL
PORT       = /dev/ttyACM0
BAUD       = 115200
PROGRAMMER = stk500v1

SRC          = echo
USART_HEADER = -I../../util
USART_SRC    = ../../util/usart.c


# Generate the executable
$(SRC).bin: $(SRC).c
	avr-gcc -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) $(USART_HEADER) -o $(SRC).bin $(SRC).c $(USART_SRC)

# Generate the hex file
$(SRC).hex: $(SRC).bin
	avr-objcopy -O ihex $(SRC).bin $(SRC).hex -j .text -j .data

# Using Arduino as flash programmer, write the code into chip's flash memory
flash: $(SRC).hex
	avrdude -p $(MCU) \
	        -b $(BAUD) \
			-C /etc/avrdude.conf \
			-c $(PROGRAMMER) \
			-P $(PORT) \
			-U flash:w:$(SRC).hex:i \
			-V -F -v -v

clean:
	rm -f *.bin *.hex


hex: $(SRC).hex
