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

IntakeControl::IntakeControl(Intake* in, Gamepad* gp) : _in(in), _gp(gp)
{

}

IntakeControl::~IntakeControl() = default;

void IntakeControl::toggle()
{

	//can't use a while loop because we want the execution to continue
	static bool should_turn = true;
	//right now dummy
	//spins until limit switch is hit
	//defaults .5

	if(_in->pressed() == true)  //if limit switch is pressed, stop the motor; otherwise keep turning at .5 speed
	{
		should_turn = false;
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

void IntakeControl::force(double speed) //sets the speed of intake motor to whatever speed you input as a parameter
{
	_in->setSpeed(speed);
}

void IntakeControl::update()
{
	auto rt = _gp->getRawAxis(CONFIGS::RT_BIND); //force button
	auto rb = _gp->getRawButton(CONFIGS::RB_BIND); //toggle button 

	//force gets priority of both force and toggle pressed
	//force speed depends on how much button is pressed
	if(rt > CONFIGS::RT_COMP)
	{
		force(rt * CONFIGS::MOTOR_SCALE); //turns motor at a speed proportional to how much rt is pressed
		return;
	}

	if(rb != false) //checks the toggle button, and toggles the motor if pressed
	{
		toggle();
		return;
	}

	//set the motor speed to 0
	constexpr unsigned char DEAD = 0; //stupid magic numbers
	force(DEAD); //if neither is pressed, stop the motor
}

