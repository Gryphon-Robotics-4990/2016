/*
 * TeleopDrivetrainController.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: user
 */

#include "DriveControllers/TeleopDrivetrainController.h"

#include "DriveBase/DriveBase.h"
#include "Controllers/Gamepad.h"
#include "Configs/Configs.h"

#include <cassert>
#include <iostream>

RobotError::RobotError(std::string what) :
		std::runtime_error(what) {

}

TeleopDrivetrainController::TeleopDrivetrainController(DriveBase* db,
		Gamepad* gp) :
		_db(db), _gp(gp) {

}

void TeleopDrivetrainController::setTurn(double throttle, double turn)
{
	//Super sensitive

	//scale throttle
	throttle *= CONFIGS::MOTOR_SCALE; //sets motor speed proportionally to position of left joystick

	double l_side; //variables that will later be used to set motor speeds
	double r_side;

	if (turn >= 0) { //for right turns
		l_side = throttle;
		r_side = throttle * (1 - 2 * turn);
	} else { //for left turns
		l_side = throttle * (1 + 2 * turn);
		r_side = throttle;
	}

	assert(l_side >= -1 && l_side <= 1); //makes sure that motor powers are between -1 and 1 to prevent errors
	assert(r_side >= -1 && r_side <= 1);

	_db->setSide(l_side, Side::Left); //sets motor speeds to l_sde and r_side
	_db->setSide(r_side, Side::Right);
}

void TeleopDrivetrainController::update() {
	/*What it does:
	 * Grabs the values from the gamepad
	 * do some math on them
	 * pass them to the drivebase
	 */

	//We use Left Y for throttle
	//And Right X for turning

	static bool toggle = false;

	if(_gp->getRawButton(5) )
	{
		//std::cout << "5" << std::endl;
		toggle = false;
	} else if(_gp->getRawButton(6) )
	{
		//std::cout << "6" << std::endl;
		toggle = true;
	}

	//std::cout << toggle << std::endl;

	//Right X is inverted? 
	double ly = _gp->getLeftY();
	double rx = -_gp->getRightX();

	if(toggle)
	{
		ly = -ly;
		rx = -rx;
	}

	//std::cout << rx << std::endl;

	setTurn(ly, rx); //sets motor speeds using ly as throttle and rx as turn
}
