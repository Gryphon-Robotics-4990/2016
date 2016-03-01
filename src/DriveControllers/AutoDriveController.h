/*
 * AutoDriveController.h
 *
 *  Created on: Feb 13, 2016
 *      Author: user
 */

#ifndef SRC_DRIVECONTROLLERS_AUTODRIVECONTROLLER_H_
#define SRC_DRIVECONTROLLERS_AUTODRIVECONTROLLER_H_

#include <memory>

class DriveBase;

class AutoDriveController
{
private:
	DriveBase* _db;
	//the bottom class is for binds
	class Robot;

	std::unique_ptr<Robot> rb;
public:
	AutoDriveController(DriveBase* db);
	~AutoDriveController();
	void run();
	void update();
};

#endif /* SRC_DRIVECONTROLLERS_AUTODRIVECONTROLLER_H_ */
