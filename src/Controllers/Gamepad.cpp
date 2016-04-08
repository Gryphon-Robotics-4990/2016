/*
 * Gamepad.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: norayu
 */

#include <Controllers/Gamepad.h>
#include <Joystick.h>

#include <cassert>

Gamepad::Gamepad(unsigned int port)
{
	_joystick = std::make_unique<Joystick>(port);
}

double Gamepad::getRightX()
{
	constexpr unsigned char X_AXIS = 4;
	return _joystick->GetRawAxis(X_AXIS);
}

double Gamepad::getRightY()
{
	constexpr unsigned char Y_AXIS = 5;
	return _joystick->GetRawAxis(Y_AXIS);
}

double Gamepad::getLeftX() {
	constexpr unsigned char X_AXIS = 0;
	return _joystick->GetRawAxis(X_AXIS);
}

double Gamepad::getLeftY() {
	constexpr unsigned char Y_AXIS = 1;
	return _joystick->GetRawAxis(Y_AXIS);
}

double Gamepad::getRawAxis(unsigned int channel)
{
	return _joystick->GetRawAxis(channel);
}

bool Gamepad::getRawButton(unsigned int channel)
{
	return _joystick->GetRawButton(channel);
}








