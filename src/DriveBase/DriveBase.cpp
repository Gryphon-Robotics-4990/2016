/*
 * DriveBase.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: norayu
 */

#include <DriveBase/DriveBase.h>

#include "Motors/Motor.h"

void DriveBase::setSide(double speed, Side side)
{
	for(auto& it : _motors)
	{
		if(it.second == side)
		{
			if(it.second == Side::Right)
			{
				it.first->setSpeed(-speed);
			}
			else
			{
				it.first->setSpeed(speed);
			}
		}
	}
}

void DriveBase::setAll(double speed)
{
	for(auto& it : _motors)
	{
		if(it.second == Side::Right)
		{
			it.first->setSpeed(-speed);
		}
		else
		{
			it.first->setSpeed(speed);
		}
	}
}

void DriveBase::setIndividual(double speed, unsigned int mw)
{

}
