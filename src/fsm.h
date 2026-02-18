#ifndef FSM_H
#define FSM_H

#include <stdint.h>  // uint8_t type
#include <stdbool.h> // bool type

#define TICK_PERIOD_IN_SECONDS 0.250 // Prescaler reaching a period of 0.249856 seconds (OCR0A = 244)
#define TICKS_PER_SECOND (1/TICK_PERIOD_IN_SECONDS)
#define SECONDS(x) (uint8_t)((x) * TICKS_PER_SECOND)

// Traffic Light States
typedef enum {
    IDLE_VEHICLE_GREEN_PEDESTRIAN_RED,
    VEHICLE_FLASHING_GREEN_PEDESTRIAN_RED,
    VEHICLE_RED_PEDESTRIAN_RED,
    VEHICLE_RED_PEDESTRIAN_GREEN,
    VEHICLE_RED_PEDESTRIAN_FLASHING_GREEN
} TrafficLightState;

/*  
    - Global Variables: To use them from the interruption handler function ISR(), which does not accept arguments. Also used in fsm.
    - Volatile: Make them possible to be read/written at any time. Compiler will not optimize them as fixed variables, because compiler could see them as not accessible from software.
                They are also accessible from ISR (hardware).
    - Extern: To make them accessible as global variables for different source files (fsm.c and mcu_isr.c). 
*/
extern volatile TrafficLightState current_state;
extern volatile TrafficLightState previous_state;
extern volatile bool pressed_button;
extern volatile uint8_t tick_counter;

// Function: Traffic Light FSM Next State
void traffic_light_fsm_next_state(
     TrafficLightState current_state_param, 
     TrafficLightState previous_state_param
);

// Function: Traffic Light FSM Execution
void traffic_light_fsm_execution(void);

#endif // FSM_H
