/*
 * TeleopDrivetrainController.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: user
 */

#include "DriveControllers/TeleopDrivetrainController.h"

#include "DriveBase/DriveBase.h"
#include "Controllers/Gamepad.h"
#include "Configs/Configs.h"

#include <cassert>
#include <iostream>
#include <cmath>

RobotError::RobotError(std::string what) :
		std::runtime_error(what) {

}

TeleopDrivetrainController::TeleopDrivetrainController(DriveBase* db,
		Gamepad* gp) :
		_db(db), _gp(gp) {

}
namespace
{
	class FindThrottle
	{
	private:
		float _prev_throttle = 0;
		float _prev_time = clock() / (double)CLOCKS_PER_SEC;
	public:
		double findThrottle(double throttle)
				{
					//stores last throttle!

					//clock returns clock ticks since epoch
					float current_time = clock() / (double)CLOCKS_PER_SEC;

					if(CONFIGS::ACCEL_TIME != 0)
					{
						double accel = (throttle - _prev_throttle) / CONFIGS::ACCEL_TIME;
						float delta_time = current_time - _prev_time;
						//converts to milliseconds
						constexpr float MILLISEC_IN_SEC = 1000;
						delta_time *= MILLISEC_IN_SEC;

						double delta_throttle = delta_time * accel;

						throttle = _prev_throttle + delta_throttle;
					}

					//sets prev time to current one
					_prev_time = current_time;

					//sets prev throttle to current one
					_prev_throttle = throttle;

					return (fabs(throttle) <= CONFIGS::THROTTLE_CUTOFF) ? 0.0 : throttle;
				}
			};
}

void TeleopDrivetrainController::setTurn(double throttle, double turn)
{
	auto calcInsideWheelSpeed = [](double outside_speed, double turn_steepness)
		{
			double turn_radius = CONFIGS::MAX_TURN_RADIUS - (CONFIGS::MAX_TURN_RADIUS * turn_steepness);

			return outside_speed * (turn_radius / (turn_radius + CONFIGS::ROBOT_WIDTH) );
		};
		double l_side;
		double r_side;

		if(turn > 0)
		{
			l_side = throttle;
			r_side = calcInsideWheelSpeed(throttle, turn);
		}
		else
		{
			l_side = calcInsideWheelSpeed(throttle, turn);
			r_side = throttle;
		}

		//TODO: IMPLEMENT REVERSE TURNING

		std::cout << r_side << std::endl;

		assert(l_side >= -1 && l_side <= 1);
		assert(r_side >= -1 && r_side <= 1);

		_db->setSide(l_side, Side::Left);
		_db->setSide(r_side, Side::Right);
	}

void TeleopDrivetrainController::setStraight(double speed)
{
		_db->setAll(speed);
}

void TeleopDrivetrainController::turnInPlace(double speed)
{
		_db->setSide(speed, Side::Left);
		_db->setSide(-speed, Side::Right);
}


void TeleopDrivetrainController::setATurn(double controller_throttle, double controller_turn)
{
	static FindThrottle ft_turn{};
		static FindThrottle ft_throt{};

		//is l side?
		double throttle = ft_throt.findThrottle(controller_throttle * CONFIGS::MOTOR_SCALE);
		double turn = ft_turn.findThrottle(controller_turn * CONFIGS::MOTOR_SCALE);

		std::cout << "CALC THROT: " << throttle << std::endl;
		std::cout << "CALC TURN: " << turn << std::endl;

		assert(throttle >= -1 && throttle <= 1);
		assert(turn >= -1 && turn <= 1);

		if(throttle != 0 && turn != 0)
		{
			setTurn(throttle, turn);
		}
		else if(throttle != 0 && turn == 0)
		{
			setStraight(throttle);
		}
		else if(throttle == 0 && turn != 0)
		{
			turnInPlace(turn);
		}
		else
		{
			const double STOP = 0.0;
			setStraight(STOP);
		}
}

void TeleopDrivetrainController::setBTurn(double throttle, double turn)
{
	//scale throttle
	throttle *= CONFIGS::MOTOR_SCALE; //sets motor speed proportionally to position of left joystick

	double l_side; //variables that will later be used to set motor speeds
	double r_side;

	if (turn >= 0) { //for right turns
		l_side = throttle;
		r_side = throttle * (1 - 2 * turn);
	 	 } else { //for left turns
	 		 l_side = throttle * (1 + 2 * turn);
	 		 r_side = throttle;
	 }

	assert(l_side >= -1 && l_side <= 1); //makes sure that motor powers are between -1 and 1 to prevent errors
	assert(r_side >= -1 && r_side <= 1);

	_db->setSide(l_side, Side::Left); //sets motor speeds to l_sde and r_side
	_db->setSide(r_side, Side::Right);
}

void TeleopDrivetrainController::update() {
	/*What it does:
	 * Grabs the values from the gamepad
	 * do some math on them
	 * pass them to the drivebase
	 */

	//We use Left Y for throttle
	//And Right X for turning

	//Right X is inverted? 
	double ly = _gp->getLeftY();
	double rx = -_gp->getRightX();

	if(CONFIGS::DRIVE_BETA)
	{
		setBTurn(ly, rx);
	}
	else
	{
		setATurn(ly, rx); //sets motor speeds using ly as throttle and rx as turn
	}
}
