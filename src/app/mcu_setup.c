/**
 * @file mcu_setup.c
 * @author Alfonso Castillo Orozco
 * @brief Microcontroller Unit ATtiny4313 Setup - Definitions
 * @version 1.0
 * @date 2026-02-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "mcu_setup.h"

// Function: MCU Setup
void mcu_setup(void) {

    // Datasheet ATtiny4313 source: https://ww1.microchip.com/downloads/en/DeviceDoc/doc8246.pdf 

    // Port Configuration: LEDs (PORTB): [0 0 0 LEDVG LEDVR LEDPG LEDPR 0]
        
        // Enabling as Outputs: 1 (PB4, PB3, PB2, PB1)=(LEDVG, LEDVR, LEDPG, LEDPR). Datasheet page 70.
        DDRB = 0x1E;

        // Setting Outputs: To set LEDs as High (1) OR Low (0).  Datasheet page 70.
        PORTB = 0x00;

    // External Interrupts Configuration: Button B1/B2
        GIMSK |= (1 << INT0 ); // Enabling Interrupts for INT0: Button B1/B2. Datasheet page 52.
        MCUCR = 0x0000; // INT0 is triggered with a Low Voltage Detection: 0 V. Datasheet pages 69 and 51.

    // Prescaler Configuration: Register TCCR0B
        TCCR0B |= 0x05; // TCCR0B[2:0] = 101 // (clkI/O / 1024)^-1: (1 Mhz / 1024)^-1 = 1.024 ms. Datasheet pages 85 and 86.

    // Internal Interrupts Configuration: Timer
        OCR0A = 244;    // Counter to reach 0.249856 s approximately 0.250 s, 8 bits: 0-255 // 1.024 ms * 244 = 0.249856 s. Datasheet page 86.
        TCCR0A |= 0x00; // TCCR0A[7:6]= [0 0]: Normal port operation. OC0A disconnected // Datasheet page 82.
        TIMSK |= 0x01;  // The Interrupt OCIE0A Bit is set to 1, which is linked to TIFR // Datasheet page 87.

    // Enables Interrupts
        sei();

}
