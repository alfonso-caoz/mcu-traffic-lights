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
