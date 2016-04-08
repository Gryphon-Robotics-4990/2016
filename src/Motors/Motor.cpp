/*
 * Motor.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: norayu
 */

#include <Motors/Motor.h>

#include <TalonSRX.h>

#include <cassert>
#include <iostream>

Motor::Motor(unsigned int channel) : _channel(channel)
{
	_motor = std::make_unique<TalonSRX>(channel);
}

Motor::~Motor()
{
	kill();
}

void Motor::setSpeed(double speed)
{
	//for debugging
	assert(-1 <= speed && speed <= 1);
	std::cout << _channel << ": " << speed << std::endl;
	_motor->Set(speed);
}

void Motor::kill()
{
	_motor->Disable();
}

unsigned int Motor::getChannel() const
{
	return _channel;
}
