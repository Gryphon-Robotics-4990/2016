/*
 * FangControl.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */


//very similar to limit switch 

#include <ExtraControllers/FangControl.h>

#include "Motors/Motor.h"
#include "Controllers/Gamepad.h"
#include "Configs/Configs.h"
#include "Sensors/HallEffectSensor.h"
#include "DriveBase/Fang.h"

FangControl::FangControl(Fang* fn, HallEffectSensor* hs, Gamepad* gp) : _fn(fn), _hs(hs), _gp(gp)
{

}

FangControl::~FangControl() = default;

void FangControl::up()
{
	//can't use a while loop because we want the execution to continue
	static bool should_turn = true;
	//right now dummy
	//spins until limit switch is hit
	//defaults .5
	constexpr double DEF_SPEED = .5; //default speed of intake motor

	if(_hs[0]->pressed() == true)  //if sensor is reached, stop the motor; otherwise keep turning at .5 speed
	{
		should_turn = false;
	}

	if(should_turn)
	{
		force(DEF_SPEED); //uses the force function below to set default speed
	}
	else
	{
		constexpr char DEAD = 0;
		force(DEAD);
	}

}

void FangControl::down()

//the only difference is that the default speed is -.5, making it turn backwards

{
	//can't use a while loop because we want the execution to continue
	static bool should_turn = true;
	//right now dummy
	//spins until limit switch is hit
	//defaults .5
	constexpr double DEF_SPEED = -.5; //default speed of intake motor

	if(_hs->pressed() == true)  //if sensor is reached, stop the motor; otherwise keep turning at .5 speed
	{
		should_turn = false;
	}

	if(should_turn)
	{
		force(DEF_SPEED); //uses the force function below to set default speed
	}
	else
	{
		constexpr char DEAD = 0;
		force(DEAD);
	}

}

void FangControl::force(double speed) //sets the speed of intake motor to whatever speed you input as a parameter
{
	_fn->setSpeed(speed);
}

void FangControl::update()
{
	auto up_btn = _gp->getRawButton(1); //force button
	auto dn_btn = _gp->getRawButton(2); //toggle button 

	//force gets priority of both force and toggle pressed
	//force speed depends on how much button is pressed
	if(up_btn != false) //checks the up button
	{
		up(); //turns fang upward until hall sensor is reached
		return;
	}

	if(dn_btn != false) //turns fang downward until hall sensor is reached
	{
		down();
		return;
	}

	//set the motor speed to 0
	constexpr unsigned char DEAD = 0; //stupid magic numbers
	force(DEAD); //if neither is pressed, stop the motor
}
