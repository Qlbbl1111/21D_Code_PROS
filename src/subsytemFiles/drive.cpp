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

void resetEncoders() {
    leftEncoder.reset();
    rightEncoder.reset();
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
//Tuning Variables
double kP = 0.0;
double kD = 0.0;

double TkP = 0.0;
double TkD = 0.0;

int error; //sensorValue - desiredValue : Postion
int pervError = 0; //postion 20ms ago
int derivative; //error - pervError : Speed

int turnError; //sensorValue - desiredValue : Postion
int turnPervError = 0; //postion 20ms ago
int turnDerivative; //error - pervError : Speed

//Variables modified for use
bool enableDrivePID = true;

void drivePID() {
    
    resetEncoders();
    inertial.tare_heading();
    while(enableDrivePID) {

        if (resetDrive) {
            resetDrive = false;
            resetEncoders();
        }
        
        int leftPosition = leftEncoder.get_value();
        int rightPosition = rightEncoder.get_value();
 
        ////////////////////////////////////////////////////
        //Lateral Movement PID
        /////////////////////////////////////////////////////////////////////////////////////////
        int averagePosition = (leftPosition + rightPosition)/2;

        //Proportional
        error = averagePosition - desiredValue;

        //Derivative
        derivative = error - pervError;

        double lateralMotorPower = (TkP * error) + (TkD * derivative);

        ////////////////////////////////////////////////////
        //Turning Movement PID
        /////////////////////////////////////////////////////////////////////////////////////////
        //int turnDiffrence = leftPosition - rightPosition;
        int turnDiffrence = inertial.get_heading();

        //Proportional
        turnPervError = turnDiffrence - desiredTurnValue;

        //Derivative
        turnDerivative = turnError - turnPervError;

        double turnMotorPower = (kP * turnError) + (kD * turnDerivative);


        /////////////////////////////////////////////////////////////////////////////////////////

        setDrive(lateralMotorPower + turnMotorPower, lateralMotorPower - turnMotorPower);
  
        pros::Task::delay(20);
    }
}