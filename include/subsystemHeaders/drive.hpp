#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right);
void setBrakeMode(int mode);
double avgDriveEndoders();
void resetEncoders();

//DRIVER CONTROL FUNCTIONS
void setDriveMotors();
void setBrake();

//AUTON FUNCTIONS
void translate(int units, int voltage);
void rotate(int degrees, int votage);
void translatePID(int units);
void rotatePID(int degrees);