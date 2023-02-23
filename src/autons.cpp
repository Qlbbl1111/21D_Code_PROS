#include "main.h"

void selectAunton(int auton) {
    switch (auton) {
        case 0:
            //None
            break;
        case 1:
            closeRoller();
            break;
        case 2:
            farRoller();
            break;
        case 3:
            skills();
            break;

    }
}
void closeRoller() {
    controller.print(0, 0, "Close Roller");
    pros::Task pid(drivePID);
    resetDrive = true;
    translateFor(6, true, 10);
    rotateTo(90, 8);
    pros::Task::delay(20);
    resetDrive = true;
    translateFor(-6, true, 10);
    rotateTo(0, 8);
}

void farRoller() {
    controller.print(0, 0, "Far Roller");
    pros::Task pid(drivePID);
}

void skills() {
    controller.print(0, 0, "Skills");
}