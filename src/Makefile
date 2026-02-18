MCU = attiny4313
F_CPU = 1000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET = main
SRC = main.c mcu_setup.c fsm.c mcu_isr.c

all:
	${CC} ${CFLAGS} -o ${TARGET}.elf ${SRC}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.elf ${TARGET}.hex

flash:
	avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb

clean:
	rm -f *.elf *.hex
