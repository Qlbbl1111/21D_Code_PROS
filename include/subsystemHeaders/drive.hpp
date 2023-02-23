#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right);
void setBrakeMode(int mode);
void resetEncoders();

//DRIVER CONTROL FUNCTIONS
void setDriveMotors();
void setBrake();

//AUTON FUNCTIONS
void drivePID();