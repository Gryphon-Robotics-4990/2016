/*
 * Fang.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

//based on intake 

#include <DriveBase/Fang.h>

#include <Motors/Motor.h>

Fang::Fang(unsigned int port)
{
	_motor = std::make_unique<Motor>(port);
}

Fang::~Fang() = default;

void Fang::setSpeed(double speed)
{
	_motor->setSpeed(speed);
}

void Fang::force(double speed)
{
	setSpeed(speed);
}
