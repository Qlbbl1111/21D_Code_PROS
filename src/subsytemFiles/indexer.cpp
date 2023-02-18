#include "main.h"

void setIndexer() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !shift()) {
        indexer = 127;
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && shift()) {
        indexer = 127;
    } else {
        indexer = 0;
    }
}