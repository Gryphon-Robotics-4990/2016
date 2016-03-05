/*
 * Fang.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

//based on intake 

#include <DriveBase/Fang.h>


#include "Motors/Motor.h"
#include "Sensors/HallEffectSensor.h"

#include <cassert>

Fang::Fang(unsigned int port, HallEffectSensor* hsa, HallEffectSensor* hsb, HallEffectSensor* hsc)
{
	_motor = std::make_unique<Motor>(port);

	_hs[0] = hsa;
	_hs[1] = hsb;
	_hs[2] = hsc;
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

HallEffectSensor* Fang::getSensor(unsigned char pos)
{
	assert(pos <= MAX_POS);
	return _hs[pos];
}
