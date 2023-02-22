#include "main.h"
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

//PNUEMATICS
extern pros::ADIDigitalOut expansion;
extern pros::ADIDigitalOut blocker;

//SHIFT
bool shift();
