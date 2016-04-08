/*
 * LimitSwitch.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

#include <Sensors/LimitSwitch.h>

#include <DigitalInput.h>

LimitSwitch::LimitSwitch(unsigned int port) : _port(port)
{
	_switch = std::make_unique<DigitalInput>(_port);
}

LimitSwitch::~LimitSwitch() = default;

bool LimitSwitch::pressed()
{
	return _switch->Get();
}
