#include "main.h"

void triggerExpansion() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) && shift())
        expansion = 1;
    else expansion = 0;
    }