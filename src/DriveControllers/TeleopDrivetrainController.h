/*
 * TeleopDrivetrainController.h
 *
 *  Created on: Feb 9, 2016
 *      Author: user
 */

#ifndef SRC_DRIVECONTROLLERS_TELEOPDRIVETRAINCONTROLLER_H_
#define SRC_DRIVECONTROLLERS_TELEOPDRIVETRAINCONTROLLER_H_

#include <stdexcept>

class DriveBase;
class Gamepad;

class RobotError : public std::runtime_error
{
public:
	RobotError(std::string what);
};

class TeleopDrivetrainController
{
private:
	DriveBase* _db;
	Gamepad* _gp;

	void setTurn(double throttle, double turn);
	void setATurn(double throttle, double turn);
	void setBTurn(double throttle, double turn);
	void setStraight(double speed);
	void turnInPlace(double speed);
public:
	TeleopDrivetrainController(DriveBase* db, Gamepad* gp);
	~TeleopDrivetrainController() = default;
	void update();
};

#endif /* SRC_DRIVECONTROLLERS_TELEOPDRIVETRAINCONTROLLER_H_ */
