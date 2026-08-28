# Configurations
MCU        = atmega328p
F_CPU      = 16000000UL
PORT       = /dev/ttyACM0
BAUD       = 115200
PROGRAMMER = stk500v1
FILE       = invaders

# Generate the executable
$(FILE).bin: $(FILE).c
	avr-gcc -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) -o $(FILE).bin $(FILE).c

# Generate the hex file
$(FILE).hex: $(FILE).bin
	avr-objcopy -O ihex $(FILE).bin $(FILE).hex -j .text -j .data

# Using Arduino as flash programmer, write the code into chip's flash memory
flash: $(FILE).hex
	avrdude -p $(MCU) \
	        -b $(BAUD) \
			-C /etc/avrdude.conf \
			-c $(PROGRAMMER) \
			-P $(PORT) \
			-U flash:w:$(FILE).hex:i \
			-V -F -v -v

clean:
	rm -f *.bin *.hex


hex: $(FILE).hex
