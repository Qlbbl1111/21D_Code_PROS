#include "main.h"

void triggerExpansion() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) && shift())
        expansion.set_value(true);
    else  expansion.set_value(false);
    }

void triggerBlocker() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) && shift())
        blocker.set_value(true);
    else  blocker.set_value(false);
    }