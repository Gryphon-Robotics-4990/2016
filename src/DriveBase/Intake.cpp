/*
 * Intake.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

#include <DriveBase/Intake.h>

#include "Sensors/LimitSwitch.h"

#include <Motors/Motor.h>

Intake::Intake(unsigned int port, LimitSwitch* ls) : _ls(ls)
{
	_motor = std::make_unique<Motor>(port);
}

Intake::~Intake() = default;

void Intake::setSpeed(double speed)
{
	_motor->setSpeed(speed);
}

bool Intake::pressed()
{
	if(_ls == nullptr)
	{
		return false;
	}
	return _ls->pressed();
}
