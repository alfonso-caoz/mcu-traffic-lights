#include <avr/interrupt.h>
#include "fsm.h"

// Interrupt Service Routine for INT0: Button B1/B2
ISR(INT0_vect) {

  /* 
    Button state is just updated when it is pressed in State 0: IDLE_VEHICLE_GREEN_PEDESTRIAN_RED (FSM).
    The FSM will be automatically executing other states after this idle State 0.
  */
  pressed_button = (current_state == IDLE_VEHICLE_GREEN_PEDESTRIAN_RED) ? true : false;

}

// Interrupt Service Routine for TIMER0
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
