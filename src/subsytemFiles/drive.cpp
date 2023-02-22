#include "main.h"
#include <string>
int brakeMode = 0;

//HELPER FUNCTIONS
void setDrive(int left, int right) {
    driveLeftBack = left;
    driveLeftFront = left;
    driveRightBack = right;
    driveRightFront = right;
}

void setBrakeMode(int mode) {
    switch (mode) {
    case 0:
        driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        break;
    case 1:
        driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        break;
    case 2:
        driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        break;
    }
}

double avgDriveEndoders() {
    return (fabs(driveLeftFront.get_position()) + fabs(driveLeftBack.get_position()) + fabs(driveLeftFront.get_position()) + fabs(driveLeftBack.get_position()))/4;
}

void resetEncoders() {
    driveLeftFront.tare_position();
    driveLeftBack.tare_position();
    driveRightFront.tare_position();
    driveRightBack.tare_position();
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

//AUTON FUNCTIONS
void translate(int units, int voltage) {
    //Define Direction
    int direction = abs(units)/units;
    //Reset Encoders
    resetEncoders();
    inertial.tare_rotation();
    //drive forward until units are reached
    while (avgDriveEndoders() < abs(units)) {
        setDrive(voltage * direction + inertial.get_rotation(), voltage * direction - inertial.get_rotation());
        pros::delay(10);
    }
    //Brief Break
    setDrive(-2*direction, -2*direction);
    pros::delay(50);
    //Reset Drive
    setDrive(0, 0);
}

void translatePID(int units) {
    int direction = abs(units)/units;
    int previousError = 0;
    int totalError = 0;
    int error = 0;

    //Tune here
    double kP = 0.57;
    double kI = 0.000002;
    //Reset Encoders
    resetEncoders();
    inertial.tare_rotation();
    //drive forward until units are reached
    while (avgDriveEndoders() < abs(units)) {
        error = units - abs(avgDriveEndoders());
        totalError += error;
        if (abs(totalError) > 127)
            totalError = 0;
        int motorPower = (error * kP + totalError * kI)*0.5;
        setDrive(motorPower + inertial.get_rotation(), motorPower - inertial.get_rotation());
        controller.print(0, 0, "Error: %d", error);
        pros::delay(20);
    }
    setDrive(-2*direction, -2*direction);
    pros::delay(50);
    //Reset Drive
    setDrive(0, 0);
    controller.print(0, 0, "Error: %d", error);
}

void rotatePID(int degrees) {
    int previousError = 0;
    int totalError = 0;
    int error = 0;

    //Tune here
    double kP = 0;
    double kI = 0;
    double kD = 0;
    //Reset Encoders
    inertial.tare_rotation();
    //drive forward until units are reached
    while (fabs(inertial.get_rotation()) < abs(degrees)) {
        error = degrees - inertial.get_rotation();
        totalError += error;
        if (abs(totalError) > 127)
            totalError = 0;
        int derivative = error - previousError;
        int motorPower = (error * kP + totalError * kI + derivative * kD)*0.25;
        setDrive(-motorPower, motorPower);
        previousError = error; 
        //cout << error;
        pros::delay(20);
    }
    //Reset Drive
    setDrive(0, 0);
}

void rotate(int degrees, int votage) {
    //Define Direction
    int direction = abs(degrees)/degrees;
    //Reset IMU
    inertial.tare_rotation();
    //Rotate until degrees are reached
    setDrive(-votage * direction, votage * direction);
    while (fabs(inertial.get_rotation()) < abs(degrees) - 5) {
        pros::delay(10);
    }
    //Coast for 100ms
    setDrive(0, 0);
    pros::delay(100);
    
    //Correct for overshoot
    if(fabs(inertial.get_rotation()) > abs(degrees)) {
        setDrive(0.5 * votage * direction, 0.5 * -votage * direction);
        while (fabs(inertial.get_rotation()) > abs(degrees)) {
            pros::delay(10);
        }
    }
    if(fabs(inertial.get_rotation()) < abs(degrees)) {
        setDrive(0.5 * -votage * direction, 0.5 * votage * direction);
        while (fabs(inertial.get_rotation()) > abs(degrees)) {
            pros::delay(10);
        }
    }
    //Reset Drive
    setDrive(0, 0);
}