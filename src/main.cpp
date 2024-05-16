#include "main.h"

#define leftBackMotor 3
#define leftFrontMotor 4
#define rightBackMotor 7
#define rightFrontMotor 8

#define cataPort 10

#define wingMotorPort 9

#define leftArmMotorPort 1
#define rightArmMotorPort 2

pros::Motor leftBack (leftBackMotor, true);
pros::Motor rightBack (rightBackMotor);
pros::Motor leftFront (leftFrontMotor, true);
pros::Motor rightFront (rightFrontMotor);
pros::Motor_Group leftWheels ({leftBack, leftFront});
pros::Motor_Group rightWheels ({rightBack, rightFront});


pros::Controller master (CONTROLLER_MASTER);

pros::Motor cata (cataPort);
pros::Motor wingMotor (wingMotorPort);

pros::Motor leftArmMotor (leftArmMotorPort, true);
pros::Motor rightArmMotor (rightArmMotorPort);

pros::Motor_Group armMotors ({leftArmMotor, rightArmMotor});




// CONSTANTS and vars ---------

int CATA_SPEED = 70;
int cataPos = 0;

/**
 * A callback function for LLEMU's center button.gfyyf
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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
 * Moves forward ft number of feet
*/
void moveForward(double ft){
	// 1 ft = 360 counts
	double counts = ft * 360;
	leftWheels.move_absolute(counts, 100);
	rightWheels.move_absolute(counts, 100);
}

void moveForward() {
	double counts = 360;
	leftWheels.move_absolute(counts, 100);
	rightWheels.move_absolute(counts, 100);
}

void moveForward(double ft, int velocity) {
	double counts = ft * 360;
	leftWheels.move_absolute(counts, velocity);
	rightWheels.move_absolute(counts, velocity);
}



void moveBackward(double ft){
	// 1 ft = 360 counts
	double counts = ft * 360;
	leftWheels.move_absolute(-counts, 100);
	rightWheels.move_absolute(-counts, 100);
}

/**
 * Turns the robot left by degrees
*/
void turnLeft(int degrees){
	// 1 degree = 3.5 counts
	int counts = degrees * 3.5;
	leftWheels.move_absolute(-counts, 100);
	rightWheels.move_absolute(counts, 100);
}

/**
 * Turns the robot right by degrees
*/
void turnRight(int degrees){
	// 1 degree = 3.5 counts
	int counts = degrees * 3.5;
	leftWheels.move_absolute(counts, 100);
	rightWheels.move_absolute(-counts, 100);
}

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
/*
An Autonomous Win Point is awarded to any Alliance that ends the Autonomous Period with the following tasks completed::

1. Removed the Triball from the Alliance’sMatch Load Zone that coincides with their Starting Tiles. 
	For example, in Figure 21, the red Alliance must remove the Triball that begins in the bottom-left Match Load Zone, adjacent to Robot 1’s Starting Tiles.
2. Scored at least one of their own Alliance Triballs in the Alliance’s own Goal.
3. Ended the Autonomous Period with at least one Robot contacting their own Elevation Bar.
4. Not violated any other rules.
*/
	bool WeNeedToHeadBackToTheBar = true; //These needs to be worked out with cooperating team before the match
	bool extraball = true; // are we on the side with the extra ball?
	bool teamred = true; //This needs to be figured out before the match

	//ALL OF THIS CODE IS UNTESTED. INDIVIDUAL LAYOUTS (blue team + extraball) CAN BE ADJUSTED AS NECESSARY
	//as of right now Red/Blue team code is copy/paste.
	int init_distance = 1500;
	int vel = 100;
	//cata.move_relative(300,vel);

	if(teamred && extraball) { 
		if(WeNeedToHeadBackToTheBar){
			moveForward(5);
			turnLeft(20);
			moveForward(1);
			turnRight(110);
			moveForward(2.3);
			moveForward(-0.2);
			turnRight(90);
			moveForward(6);
			turnRight(90);
			moveForward(2.1);
		} else{
			turnLeft(70); // now we should be facing the extra ball
			leftWheels.move_absolute(init_distance * 2,vel);
			rightWheels.move_absolute(init_distance * 2,vel);
			turnRight(100); // we should now be facing the ball in the middle with the red triball & extra triball in front of the robot
			leftWheels.move_absolute(init_distance * 1.3,vel);
			rightWheels.move_absolute(init_distance * 1.3,vel);
			turnRight(60);
			leftWheels.move_absolute(init_distance,vel);
			rightWheels.move_absolute(init_distance,vel);// if all goes well & this executes right we will have 2-3 triballs in our goal
		}
	} 
	else if(!(teamred) && extraball){
		
		if(WeNeedToHeadBackToTheBar){
			// Add working code
		} else{
			// Add working code
		}
	} 
	
	else if(teamred && !(extraball)){
		
		if(WeNeedToHeadBackToTheBar){
			// Add working code
		} else{
			// Add working code
		}
	} 
	
	else{
		
		if(WeNeedToHeadBackToTheBar){
			// Add working code
		} else{
			// Add working code
		}
	}
	pros::delay(2000);

	cata.move_relative(300,vel);

	/**move backward and forward align*/
	moveBackward(1.41);
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
	// NOTE TO AYAAN: MOTORS DEFINED UP TOP
	float scaleFactor = 1.00;
  while (true) {

	// variable collection
	cata.set_encoder_units(MOTOR_ENCODER_COUNTS);



	// Get drivetrain power per side
	// float scaleFactor is moved out of while loop
	int power = master.get_analog(ANALOG_LEFT_Y)*scaleFactor;
    int turn = -1*master.get_analog(ANALOG_RIGHT_X)*scaleFactor;
    //float left = copysign((pow(power - turn, 2) ) / 100, power - turn);
    //float right = copysign((pow(power + turn , 2) ) / 100, power + turn);
	float left = power - turn;

	float right = power + turn;

	//float left = master.get_analog(ANALOG_LEFT_Y);
	//float right = master.get_analog(ANALOG_RIGHT_Y);
	//left *= scaleFactor;
	//right *= scaleFactor;

	// Drivetrain
	leftWheels.move(left);
	rightWheels.move(right); // negated cuz the motors was lowk flipped

	// Catapult
	cataPos = cata.get_position(); //  getting absolute 
	if(master.get_digital(DIGITAL_UP)){
		cata.move_velocity(-CATA_SPEED);
	} else if (master.get_digital(DIGITAL_DOWN)){ // engaged 
		cata.move_velocity(CATA_SPEED); 
	} else {
		cata.set_brake_mode(MOTOR_BRAKE_HOLD);
		cata.move_velocity(0);

		// keep moving to last known position
		cata.move_absolute(cataPos, 100);
	}

	// Wings
	if(master.get_digital(DIGITAL_R1)){
		wingMotor.move_velocity(100);
	} else if (master.get_digital(DIGITAL_R2)){
		wingMotor.move_velocity(-100);
	} else {
		wingMotor.move_velocity(0);

	}

	// Arm
	if(master.get_digital(DIGITAL_X)){
		armMotors.move_velocity(100);
	} else if (master.get_digital(DIGITAL_B)){
		armMotors.move_velocity(-100);
	} else {
		leftArmMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
		rightArmMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
		armMotors.move_velocity(0);
	}

	


//delay ig
    pros::delay(2);
	}
}

// testing github commits
