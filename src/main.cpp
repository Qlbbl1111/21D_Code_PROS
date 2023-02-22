#include "main.h"

int autonSelect = 0;
int auton = 0;

/**
 * A callback function for LLEMU's center button.
 */
void on_center_button() {
	auton = autonSelect;
	switch (auton) {
		case 0:
			pros::lcd::set_text(4, "Not running auton.");
			break;
		case 1:
			pros::lcd::set_text(4, "Running auton: Close Roller");
			break;
		case 2:
			pros::lcd::set_text(4, "Running auton: Far Roller");
			break;
		case 3:
			pros::lcd::set_text(4, "Running auton: Skills");
			break;
	}
} 

/**
 * A callback function for LLEMU's left button.
 */
void on_left_button() {
	switch (autonSelect) {
		case 0:
			autonSelect = 1;
			pros::lcd::set_text(2, "Slected auton: Close Roller");
			auton = 0;
			pros::lcd::set_text(4, "Not running auton.");
			break;
		case 1:
			autonSelect = 2;
			pros::lcd::set_text(2, "Slected auton: Far Roller");
			auton = 0;
			pros::lcd::set_text(4, "Not running auton.");
			break;
		case 2:
			autonSelect = 3;
			pros::lcd::set_text(2, "Slected auton: Skills");
			auton = 0;
			pros::lcd::set_text(4, "Not running auton.");
			break;
		case 3:
			autonSelect = 0;
			pros::lcd::set_text(2, "No auton selected.");
			auton = 0;
			pros::lcd::set_text(4, "Not running auton.");

			break;

	}
}

/**
 * A callback function for LLEMU's right button.
 */
void on_right_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
	} else {}
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	inertial.reset();
	while (inertial.is_calibrating()) {
		pros::delay(100);
	}
	pros::lcd::initialize();
	pros::lcd::set_background_color(241, 0, 145);
	pros::lcd::set_text(0, "21D - Auton Select ");
	pros::lcd::set_text(2, "No auton selected.");
	pros::lcd::set_text(4, "Not running auton.");
	pros::lcd::set_text(6, "Left: Select auton.");
	pros::lcd::set_text(7, "Center: Confirm auton.");
	pros::lcd::register_btn0_cb(on_left_button);
	pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn2_cb(on_right_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	setBrakeMode(0);
	selectAunton(auton);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	setBrakeMode(2);
	while (true)
	{
		setDriveMotors();
		setFlywheelMotors();
		setIntake();
		setIndexer();
		triggerExpansion();

		pros::delay(20);
	}
	
}
