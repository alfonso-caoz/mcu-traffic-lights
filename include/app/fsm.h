/**
 * @file fsm.h
 * @author Alfonso Castillo Orozco
 * @brief Traffic Light Finite State Machine - Declarations
 * @version 1.0
 * @date 2026-02-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef FSM_H
#define FSM_H

#include <stdint.h>  // uint8_t type
#include <stdbool.h> // bool type


/**
 * @defgroup TIME_INTERRUPT_GROUP Time Interrupt Group
 * @brief A group to manage the time interrupts.
 * 
 * @{
 */

/** @brief After the Prescaler and Internal Interrupt setup, this interrupt period was set to 250 ms = 0.250 s. */
#define TICK_PERIOD_IN_SECONDS 0.250 // Prescaler reaching a period of 0.249856 seconds (OCR0A = 244)

/** @brief Calculates how many ticks are counted in one second at a determined period. */
#define TICKS_PER_SECOND (1/TICK_PERIOD_IN_SECONDS)

/** @brief Sets the expected time frame in seconds, instead of number of ticks. Example: 1 s, instead of 4 ticks. */
#define SECONDS(x) (uint8_t)((x) * TICKS_PER_SECOND)

/** @} */ // Group Documentation Ends


/**
 * @brief Enumeration of all Traffic Light States
 * 
 * @dot
 * digraph Traffic_Light_FSM {
 *     
 *     rankdir=UD; // Graph Orientation: Left to Right
 *     
 *     // Defining States
 *     IDLE_VEHICLE_GREEN_PEDESTRIAN_RED        [shape=box, style="filled", color=darkgreen];
 *     VEHICLE_FLASHING_GREEN_PEDESTRIAN_RED    [shape=box, style="filled", color=lightgreen];
 *     VEHICLE_RED_PEDESTRIAN_RED               [shape=box, style="filled", color=red];
 *     VEHICLE_RED_PEDESTRIAN_GREEN             [shape=box, style="filled", color=darkgreen];
 *     VEHICLE_RED_PEDESTRIAN_FLASHING_GREEN    [shape=box, style="filled", color=lightgreen];
 *     
 *     
 *     // Defining State Transitions and Labels
 *     IDLE_VEHICLE_GREEN_PEDESTRIAN_RED -> VEHICLE_FLASHING_GREEN_PEDESTRIAN_RED   [label="Button Pressed + Time >= 10 s"];
 *     VEHICLE_FLASHING_GREEN_PEDESTRIAN_RED -> VEHICLE_RED_PEDESTRIAN_RED          [label="Time = 3 s"];
 *     VEHICLE_RED_PEDESTRIAN_RED -> VEHICLE_RED_PEDESTRIAN_GREEN                   [label="Time = 1 s"];
 *     VEHICLE_RED_PEDESTRIAN_GREEN -> VEHICLE_RED_PEDESTRIAN_FLASHING_GREEN        [label="Time = 10 s"];
 *     VEHICLE_RED_PEDESTRIAN_FLASHING_GREEN -> VEHICLE_RED_PEDESTRIAN_RED          [label="Time = 3 s"];
 *     VEHICLE_RED_PEDESTRIAN_RED -> IDLE_VEHICLE_GREEN_PEDESTRIAN_RED              [label="Time = 1 s"];
 * 
 * } 
 * @enddot
 * @details This diagram illustrates the states and transitions for the Traffic Light FSM.
 */
typedef enum {
    IDLE_VEHICLE_GREEN_PEDESTRIAN_RED,      ///< State 0: Idle State waiting for an Interruption. Vehicle has a green light, and Pedestrian a red light. Commute: Button B1/B2 pressed & Time >= 10 s.
    VEHICLE_FLASHING_GREEN_PEDESTRIAN_RED,  ///< State 1: Vehicle has a flashing green light, and Pedestrian a red light. Commute: Time = 3 s. Flashing every 0.5 s.
    VEHICLE_RED_PEDESTRIAN_RED,             ///< State 2: Vehicle and Pedestrian have red lights. Commute: Time = 1 s.
    VEHICLE_RED_PEDESTRIAN_GREEN,           ///< State 3: Vehicle has a red light, and Pedestrian a green light. Commute: Time = 10 s.
    VEHICLE_RED_PEDESTRIAN_FLASHING_GREEN   ///< State 4: Vehicle has a red light, and Pedestrian a flashing green light. Commute: Time = 3 s. Flashing every 0.5 s.
} TrafficLightState;


/*
    - Global Variables: To use them from the interruption handler function ISR(), which does not accept arguments. Also used in fsm.c file.
    - Volatile: Make them possible to be read/written at any time. Compiler will not optimize them as fixed variables, because compiler could see them as not accessible from software.
                They are also accessible from ISR (hardware).
    - Extern: To make them accessible as global variables for different source files (fsm.c and mcu_isr.c). 
*/
extern volatile TrafficLightState current_state;    ///< Global variable: Current State of FSM.
extern volatile TrafficLightState previous_state;   ///< Global variable: Previous State of FSM.
extern volatile bool pressed_button;                ///< Global variable: Button B1/B2 State (External Interrupt).
extern volatile uint8_t tick_counter;               ///< Global variable: Tick Counter (Internal Interrupt: Timer).


/**
 * @brief Function: Traffic Light FSM Next State
 * 
 * This function sets the global variables for the next state, it makes the FSM commute.
 * 
 * @param[in] current_state_param Sets the next value (next FSM state) for global variable @ref current_state.
 * @param[in] previous_state_param Sets the next value (next FSM State) for global variable @ref previous_state.
 */
void traffic_light_fsm_next_state(
     TrafficLightState current_state_param, 
     TrafficLightState previous_state_param
);


/**
 * @brief Function: Traffic Light FSM Execution
 * 
 * This function triggers the Traffic Light State Machine, passing through all the states defined in @ref TrafficLightState.
 * 
 */
void traffic_light_fsm_execution(void);

#endif // FSM_H
