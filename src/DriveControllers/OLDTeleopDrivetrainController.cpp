/*
 * TeleopDrivetrainController.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: user
 */

#include "DriveControllers/TeleopDrivetrainController.h"

#include "DriveBase/DriveBase.h"
#include "Controllers/Gamepad.h"

#include <cassert>

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

	double l_side;
	double r_side;

	if (turn >= 0) {
		l_side = throttle;
		r_side = throttle * (1 - 2 * turn);
	} else {
		l_side = throttle * (1 + 2 * turn);
		r_side = throttle;
	}

	assert(l_side >= -1 && l_side <= 1);
	assert(r_side >= -1 && r_side <= 1);

	_db->setSide(l_side, Side::Left);
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

	//Left Y is inverted.
	double ly = -_gp->getLeftY();
	double rx = _gp->getRightX();

	setTurn(ly, rx);
}
