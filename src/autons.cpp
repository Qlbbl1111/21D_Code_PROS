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
    translatePID(500);
    //rotatePID(90);
}

void farRoller() {
    controller.print(0, 0, "Far Roller");
    translate(500, 90);
}

void skills() {
    controller.print(0, 0, "Skills");
}