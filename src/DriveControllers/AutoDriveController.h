/*
 * AutoDriveController.h
 *
 *  Created on: Feb 13, 2016
 *      Author: user
 */

#ifndef SRC_DRIVECONTROLLERS_AUTODRIVECONTROLLER_H_
#define SRC_DRIVECONTROLLERS_AUTODRIVECONTROLLER_H_

#include <memory>
#include <ctime>

class DriveBase;
class Fang;
class Intake;
class AutoDriveController
{
private:
	std::time_t _starttime;
	DriveBase* _db;
	Fang* _fng;
	Intake* _in;
	//the bottom class is for binds
	class Robot;

	std::unique_ptr<Robot> rb;
public:
	AutoDriveController(DriveBase* db, Fang* fng, Intake* in);
	~AutoDriveController();
	void run();
	void update();
};

#endif /* SRC_DRIVECONTROLLERS_AUTODRIVECONTROLLER_H_ */
