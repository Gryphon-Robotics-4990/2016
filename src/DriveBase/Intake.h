/*
 * Intake.h
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

#ifndef SRC_DRIVEBASE_INTAKE_H_
#define SRC_DRIVEBASE_INTAKE_H_

#include <memory>

class Motor;
class LimitSwitch;

class Intake
{
private:
	std::unique_ptr<Motor> _motor;
	LimitSwitch* _ls;

public:
	Intake(unsigned int port, LimitSwitch* ls);
	~Intake();
	void setSpeed(double speed);
	bool pressed();
};

#endif /* SRC_DRIVEBASE_INTAKE_H_ */
