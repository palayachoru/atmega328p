# Configurations
MCU        = atmega328p
F_CPU      = 16000000UL
PORT       = /dev/ttyACM0
BAUD       = 115200
PROGRAMMER = stk500v1


# Generate the executable
blinky.bin: blinky.c
	avr-gcc -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) -o blinky.bin blinky.c

# Generate the hex file
blinky.hex: blinky.bin
	avr-objcopy -O ihex blinky.bin blinky.hex -j .text -j .data

# Using Arduino as flash programmer, write the code into chip's flash memory
flash: blinky.hex
	avrdude -p $(MCU) \
	        -b $(BAUD) \
			-C /etc/avrdude.conf \
			-c $(PROGRAMMER) \
			-P $(PORT) \
			-U flash:w:blinky.hex:i \
			-V -F -v -v

clean:
	rm -f *.bin *.hex


hex: blinky.hex
