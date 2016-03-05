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

FangControl::FangControl(Fang* fn, HallEffectSensor* hsa, HallEffectSensor* hsb, HallEffectSensor* hsc, Gamepad* gp) : _fn(fn), _gp(gp)
{
	//??? The starting pos. Dummy value of zero for now.
	_pos = CONFIGS::START_FANG_POS;

	_hs[0] = hsa;
	_hs[1] = hsb;
	_hs[2] = hsc;
}

FangControl::~FangControl() = default;

void FangControl::up() 
{
	if(_pos == MAX_POS) //will not turn if it is at its highest postion
	{
		return;
	}

	//can't use a while loop because we want the execution to continue
	static bool should_turn = true;
	//right now dummy
	//spins until limit switch is hit
	//defaults .5

	if(_hs[_pos + 1]->pressed() == true)  //if sensor is reached, stop the motor; otherwise keep turning at .5 speed
	{
		should_turn = false;
		_pos = _pos + 1; //sets position to its new position, idk if the syntax is right
	}

	if(should_turn)
	{
		force(CONFIGS::DEF_SPEED); //uses the force function below to set default speed
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

	if(_pos == 0) //will not turn if it is at its lowest position
	{
		return;
	}
	//can't use a while loop because we want the execution to continue
	static bool should_turn = true;
	//right now dummy
	//spins until limit switch is hit
	//defaults .5
	constexpr double DEF_SPEED = -.5; //default speed of intake motor

	if(_hs[_pos - 1]->pressed() == true)  //if sensor is reached, stop the motor; otherwise keep turning at .5 speed
	{
		should_turn = false;
		_pos = _pos - 1; //sets position to its new position, idk if the syntax is right
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

	//will go up if both buttons are pressed, so be careful not to press both
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
