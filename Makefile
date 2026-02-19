MCU = attiny4313
F_CPU = 1000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
INCLUDE_FLAG = -Iinclude/app
CFLAGS = -std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} ${INCLUDE_FLAG}
TARGET = build/main
SRC = src/main.c src/app/*.c

all:
	${CC} ${CFLAGS} -o ${TARGET}.elf ${SRC}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.elf ${TARGET}.hex

flash:
	avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb

clean:
	rm -f build/*.elf build/*.hex
