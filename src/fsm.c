#include <avr/io.h>
#include "fsm.h"

volatile TrafficLightState current_state = IDLE_VEHICLE_GREEN_PEDESTRIAN_RED; // Initial State
volatile TrafficLightState previous_state;
volatile bool pressed_button = false;
volatile uint8_t tick_counter = 0;

// Function: Traffic Light FSM Next State
void traffic_light_fsm_next_state(
     TrafficLightState current_state_param,
     TrafficLightState previous_state_param
) {

  // Initial Conditions Reset
  pressed_button = false;
  tick_counter = 0;

  // Next State
  current_state = current_state_param;
  previous_state = previous_state_param;

}

// Function: Traffic Light FSM Execution
void traffic_light_fsm_execution(void) {

    // FSM
    switch(current_state){
    
      // LEDs (PORTB): [0 0 0 LDPV LDVD LDPP LDPD 0]
    
      //////////////// State: 0 ////////////////////////////////
      case IDLE_VEHICLE_GREEN_PEDESTRIAN_RED:
        
        PORTB = 0x12; // LED ON: LDPV and LDPD
        
        break;
      /////////////// State: 1 ////////////////////////////////
      case VEHICLE_FLASHING_GREEN_PEDESTRIAN_RED:

        // tick_counter == 12: 2.998272 s : 3 s
        if (tick_counter == SECONDS(3)) {

          // Traffic Light FSM Next State (current_state, previous_state)
          traffic_light_fsm_next_state(VEHICLE_RED_PEDESTRIAN_RED, VEHICLE_FLASHING_GREEN_PEDESTRIAN_RED);
        
        }
        else {
          // LDPV state commutes every 0.5 s: Flashing LED (XOR)
          if ((tick_counter % SECONDS(0.5)) == 0) PORTB ^= (1 << PB4);
        }

        break;
      /////////////// State: 2 ////////////////////////////////
      case VEHICLE_RED_PEDESTRIAN_RED:
        
        PORTB = 0x0A; // LED ON: LDVD and LDPD
        
        // tick_counter == 4: 0.999424 s : 1 s
        if (tick_counter == SECONDS(1)) {
  
          // Traffic Light FSM Next State (current_state, previous_state)
          if (previous_state == VEHICLE_FLASHING_GREEN_PEDESTRIAN_RED) {
              traffic_light_fsm_next_state(VEHICLE_RED_PEDESTRIAN_GREEN, VEHICLE_RED_PEDESTRIAN_RED);
          } else if (previous_state == VEHICLE_RED_PEDESTRIAN_FLASHING_GREEN) {
              traffic_light_fsm_next_state(IDLE_VEHICLE_GREEN_PEDESTRIAN_RED, VEHICLE_RED_PEDESTRIAN_RED);
          }

        }

        break;
      /////////////// State: 3 ////////////////////////////////
      case VEHICLE_RED_PEDESTRIAN_GREEN:
        
        PORTB = 0x0C; // LED ON: LDVD and LDPP
        
        // tick_counter == 40: 9.99424 s : 10 s
        if (tick_counter >= SECONDS(10)) {

          // Traffic Light FSM Next State (current_state, previous_state)
          traffic_light_fsm_next_state(VEHICLE_RED_PEDESTRIAN_FLASHING_GREEN, VEHICLE_RED_PEDESTRIAN_GREEN);

        }

        break;
      /////////////// State: 4 ////////////////////////////////
      case VEHICLE_RED_PEDESTRIAN_FLASHING_GREEN:

        // tick_counter == 12: 2.998272 s : 3 s
        if (tick_counter == SECONDS(3)) {

          // Traffic Light FSM Next State (current_state, previous_state)
          traffic_light_fsm_next_state(VEHICLE_RED_PEDESTRIAN_RED, VEHICLE_RED_PEDESTRIAN_FLASHING_GREEN);

        }
        else {
          // LDPP state commutes every 0.5 s: Flashing LED (XOR)
          if ((tick_counter % SECONDS(0.5)) == 0) PORTB ^= (1 << PB2); 
        }

        break;
      /////////////// State by Default ////////////////////////////////
      default: 
        
        // State 0 by Default
        current_state = IDLE_VEHICLE_GREEN_PEDESTRIAN_RED;

        break;
      ///////////////////////////////////////////////////
    }
}
