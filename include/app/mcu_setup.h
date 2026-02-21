/**
 * @file mcu_setup.h
 * @author Alfonso Castillo Orozco
 * @brief Microcontroller Unit ATtiny4313 Setup - Declarations
 * @version 1.0
 * @date 2026-02-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef MCU_SETUP_H
#define MCU_SETUP_H

/**
 * @brief Function: MCU Setup
 * 
 * This function sets the following five items:
 *  1. Port Configuration: LED ports enabled as outputs and initialized as turned off.
 *     (LEDs: LEDVG, LEDVR, LEDPG, LEDPR) = (Ports: PB4, PB3, PB2, PB1)
 *  2. External Interrupts Configuration: Button B1/B2. 
 *  3. Prescaler Configuration: Period from 1.024 ms to 250 ms.
 *  4. Internal Interrupts Configuration: Timer (tick_counter) with a 250 ms period.
 *  5. Enabling Interrupts.
 */
void mcu_setup(void);

#endif // MCU_SETUP_H
