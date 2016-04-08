/*
 * Gamepad.h
 *
 *  Created on: Jan 22, 2016
 *      Author: norayu
 */

#ifndef SRC_CONTROLLERS_GAMEPAD_H_
#define SRC_CONTROLLERS_GAMEPAD_H_

#include <memory>
/*
 * Gamepad should
 * get Right X and Y Axis
 * get Left X and Y Axis
 * have a function to get state of any button by number
 */

class Joystick;

class Gamepad {
private:
	std::unique_ptr<Joystick> _joystick;
public:
	Gamepad(unsigned int port);
	double getRightX();
	double getRightY();
	double getLeftX();
	double getLeftY();
	bool getRawButton(unsigned int channel);
	double getRawAxis(unsigned int channel);
};

#endif /* SRC_CONTROLLERS_GAMEPAD_H_ */
