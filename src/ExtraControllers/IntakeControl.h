/*
 * IntakeControl.h
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

#ifndef SRC_EXTRACONTROLLERS_INTAKECONTROL_H_
#define SRC_EXTRACONTROLLERS_INTAKECONTROL_H_

#include <memory>

class Intake;
class Gamepad;

class IntakeControl
{
private:
	Intake* _in;
	Gamepad* _gp;

	void toggle();
	//defaults to .5
	void force(double speed = .5);
public:
	IntakeControl(Intake* in, Gamepad* gp);
	~IntakeControl();

	void update();
};

#endif /* SRC_EXTRACONTROLLERS_INTAKECONTROL_H_ */
