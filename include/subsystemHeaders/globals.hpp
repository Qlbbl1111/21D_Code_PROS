#include "main.h"

//VARIBLES
/**
 * Returns pi to 20 decimal places. 
 */
const double pi;
/**
 * The desired value to drive for. In degrees.. 
 */
int desiredValue;
/**
 * The desired value to turn for. In degrees. 
 */
int desiredTurnValue;
/**
 * Translates the robot a certain distance. Disance(Degrees/Inches), Unit(True for inches, false for degrees).
 */

int maxVoltage;

double translateFor(double distence, bool unit, int voltage);
/**
 * Turns the robot to a certain heading. Heading(Degrees)
 */
double rotateTo(double heading, int voltage);

bool resetDrive;

//MOTORS
extern pros::Motor intake;
extern pros::Motor indexer;
extern pros::Motor flywheel_a;
extern pros::Motor flywheel_b;
extern pros::Motor_Group flywheel;

extern pros::Motor driveRightBack;
extern pros::Motor driveRightFront;
extern pros::Motor driveLeftBack;
extern pros::Motor driveLeftFront;


//CONTROLLER
extern pros::Controller controller;

//SENSORS
extern pros::Imu inertial;
extern pros::ADIDigitalIn select;
extern pros::ADIDigitalIn confirm;
extern pros::ADIEncoder leftEncoder;
extern pros::ADIEncoder rightEncoder;


//PNUEMATICS
extern pros::ADIDigitalOut expansion;
extern pros::ADIDigitalOut blocker;
extern pros::ADIDigitalOut compesser;

//SHIFT
bool shift();