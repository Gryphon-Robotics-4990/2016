/*
 * HallEffectSensor.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

//literally the same thing as a limit switch 

#include <Sensors/HallEffectSensor.h>

#include <DigitalInput.h>

HallEffectSensor::HallEffectSensor(unsigned int port) : _port(port)
{
	_switch = std::make_unique<DigitalInput>(_port);
}

HallEffectSensor::~HallEffectSensor() = default;

bool HallEffectSensor::pressed()
{
	return _switch->Get();
}
