/**
 * @file mcu_isr.c
 * @author Alfonso Castillo Orozco
 * @brief Microcontroller Unit ATtiny4313 Interrupt Service Routine - Definitions
 * @version 0.1
 * @date 2026-02-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <avr/interrupt.h>
#include "fsm.h"


/**
 * @brief Interrupt Service Routine for INT0: Button B1/B2
 * 
 * This ISR routine detects when the Button B1/B2 was pressed, and it will set the global variable @ref pressed_button as @p true just if the Current State is @ref IDLE_VEHICLE_GREEN_PEDESTRIAN_RED.
 * 
 */
ISR(INT0_vect) {

  /* 
    Button state is just updated when it is pressed in State 0: IDLE_VEHICLE_GREEN_PEDESTRIAN_RED (FSM).
    The FSM will be automatically executing other states after this idle State 0.
  */
  pressed_button = (current_state == IDLE_VEHICLE_GREEN_PEDESTRIAN_RED) ? true : false;

}


/**
 * @brief Interrupt Service Routine for TIMER0
 * 
 * This ISR routine implements a tick counter to use it as a timer for every FSM State.
 * 
 * Also, this ISR routine checks if the following three conditions were satisfied to move out of the Idle State 0 (@ref IDLE_VEHICLE_GREEN_PEDESTRIAN_RED):
 *  1. Current State: @ref IDLE_VEHICLE_GREEN_PEDESTRIAN_RED.
 *  2. Button was pressed during this Current State.
 *  3. This Current State was active at least 10 seconds before commuting to another state.
 * 
 */
ISR(TIMER0_COMPA_vect) {

  ++tick_counter;

  ///////////////////////////// State 0 //////////////////////////////
  // tick_counter == 40: 9.99424 s : 10 s
  if ((current_state == IDLE_VEHICLE_GREEN_PEDESTRIAN_RED) && pressed_button && (tick_counter >= SECONDS(10))) {

    // Traffic Light FSM Next State (current_state, previous_state)
    traffic_light_fsm_next_state(VEHICLE_FLASHING_GREEN_PEDESTRIAN_RED, IDLE_VEHICLE_GREEN_PEDESTRIAN_RED);

  }
  ////////////////////////////////////////////////////////////////////

}
