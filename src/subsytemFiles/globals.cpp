#include "main.h"

//VARIBLES
const double pi = 3.14159265358979323846;
int desiredValue = 0;
int desiredTurnValue = 0;
int maxVoltage = 12;
double translateFor(double distence, bool unit, int voltage) {
    maxVoltage = voltage;
    if(unit) {
        desiredValue = 6.0*pi * desiredValue/360.0;
    }else {
        desiredValue = distence;
    }
}
double rotateTo(double heading, int voltage) {
    maxVoltage = voltage;
    desiredTurnValue = heading;
}

bool resetDrive = false;
//MOTORS
pros::Motor intake(7, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor indexer(21, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor_Group flywheel({flywheel_a, flywheel_b});
pros::Motor flywheel_a(1, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheel_b(2, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor driveRightBack(17, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(18, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(11, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftFront(12, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);

//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//SENSORS
pros::Imu inertial(16);
pros::ADIDigitalIn select('D');
pros::ADIEncoder leftEncoder('E', 'F', false);
pros::ADIEncoder rightEncoder('G', 'H ', true);


//PNUEMATICS
pros::ADIDigitalOut expansion('A');
pros::ADIDigitalOut blocker('B');
pros::ADIDigitalOut compesser('C');

//SHIFT
bool shift() {
    return controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
}
