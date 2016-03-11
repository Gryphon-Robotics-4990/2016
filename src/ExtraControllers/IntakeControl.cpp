/*
 * IntakeControl.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

#include <ExtraControllers/IntakeControl.h>

#include "Motors/Motor.h"
#include "Controllers/Gamepad.h"
#include "Configs/Configs.h"
#include "Sensors/LimitSwitch.h"
#include "DriveBase/Intake.h"

#include <ctime>
#include <iostream>

IntakeControl::IntakeControl(Intake* in, Gamepad* gp) : _in(in), _gp(gp)
{

}

IntakeControl::~IntakeControl() = default;

void IntakeControl::toggle()
{
	static double end_time;
	static bool is_ball_in = false;
	//can't use a while loop because we want the execution to continue
	static bool should_turn = true;
	//right now dummy
	//spins until limit switch is hit
	//defaults .5

	if(_in->pressed() == true)  //if limit switch is pressed, stop the motor; otherwise keep turning at .5 speed
	{
		should_turn = false;
		is_ball_in = true;
	}

	if(is_ball_in && should_turn)
	{
		//expell for 5 s
		if(end_time == NULL)
		{
			end_time = std::time(nullptr) + 3;
		}

		if(std::time(nullptr) > end_time)
		{
			should_turn = false;
			is_ball_in = false;
		}

	}

	if(should_turn)
	{
		force((is_ball_in) ? -CONFIGS::DEF_SPEED : CONFIGS::DEF_SPEED); //uses the force function below to set default speed
	}
	else
	{
		constexpr char DEAD = 0;
		force(DEAD);
	}

}

void IntakeControl::force(double speed) //sets the speed of intake motor to whatever speed you input as a parameter
{
	_in->setSpeed(speed);
}

void IntakeControl::update()
{
	auto rt = _gp->getRawAxis(CONFIGS::RT_BIND); //force in button
	auto lt = _gp->getRawAxis(CONFIGS::LT_BIND); //force out button
	auto rb = _gp->getRawButton(CONFIGS::RB_BIND); //toggle button 

	//force gets priority of both force and toggle pressed
	//force speed depends on how much button is pressed
	if(lt > CONFIGS::LT_COMP)
	{
		force(-lt * CONFIGS::INTAKE_SCALE);
		return;
	}

	if(rt > CONFIGS::RT_COMP)
	{
		force(rt * CONFIGS::INTAKE_SCALE); //turns motor at a speed proportional to how much rt is pressed
		return;
	}

	if(rb != false) //checks the toggle button, and toggles the motor if pressed
	{
		//toggle();
		return;
	}

	//set the motor speed to 0
	constexpr unsigned char DEAD = 0; //stupid magic numbers
	force(DEAD); //if neither is pressed, stop the motor
}

