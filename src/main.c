/**
 * @file main.c
 * @author Alfonso Castillo Orozco
 * @brief This is the main entry point for the MCU Traffic Light project.
 * @version 1.0
 * @date 2026-02-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "mcu_setup.h"
#include "fsm.h"

int main(void) {

  // Setup
  mcu_setup();

  // Loop
  while (1) {
    traffic_light_fsm_execution();
  }

  return 0;

}
