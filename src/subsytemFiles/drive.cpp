#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right) {
    driveLeftBack = left;
    driveLeftFront = left;
    driveRightBack = right;
    driveRightFront = right;
}

//DRIVER CONTROL FUNCTIONS
void setDriveMotors() {
    double t = 7;
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    if (abs(leftJoystick) < 5)
        leftJoystick = 0;
    if (abs(rightJoystick) < 5)
        rightJoystick = 0;
    int new_left =  (exp(-(t/10))+exp((abs(leftJoystick)-100)/10)*(1- exp(-(t/10))))*leftJoystick;
    int new_right = (exp(-(t/10))+exp((abs(rightJoystick)-100)/10)*(1- exp(-(t/10))))*rightJoystick;
    setDrive(new_left, new_right);
}