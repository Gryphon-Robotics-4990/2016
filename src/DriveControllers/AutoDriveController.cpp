/*
 * AutoDriveController.cpp
 *
 *  Created on: Feb 13, 2016
 *      Author: user
 */

#include <DriveControllers/AutoDriveController.h>

#include "DriveBase/DriveBase.h"
#include "Configs/CONFIGS.h"

#include <ctime>
#include <cmath>

class AutoDriveController::Robot
{
private:
	AutoDriveController* const _adc;
public:
	Robot(AutoDriveController* adc) : _adc(adc){};

	//class to have all of the robot command binds!
	void travel(double metres)
	{
		//implement!
		//no encoders so we have to guess :(

		//assuming time_t is seconds
		auto end_time = std::time(nullptr) + (std::abs(metres) / CONFIGS::MAX_SPEED);
		
		//no longer uses a while loop; uses the bool should_move instead
		if(metres > 0) //to go forwards
		{
			static bool should_move = true;
			
			if(std::time(nullptr) >= end_time)
			{
				should_move = false;
			}
			if(should_move)
			{
				_adc->_db->setAll(CONFIGS::MOTOR_SCALE);
			}
		}
		else if(metres < 0) //to go backwards
		{
			static bool should_move = true;
			
			if(std::time(nullptr) >= end_time)
			{
				should_move = false;
			}
			if(should_move)
			{
				_adc->_db->setAll(-CONFIGS::MOTOR_SCALE);
			}
		}
	}

	//clockwise
	void turn(double degrees)
	{
		//assuming degrees!
		constexpr int deg_in_circle = 360;
		double distance = (CONFIGS::ROBOT_WIDTH * M_PI) * (degrees / deg_in_circle); //arc length of the turn

		constexpr char double_motors = 2;
		auto end_time = std::time(nullptr) + (std::abs(distance) / (CONFIGS::MAX_SPEED * double_motors)); //distance = speed * time. I still think this might turn half the intended angle.

		//no longer uses a while loop; uses bool should_turn instead
		if(degrees > 0) //clockwise
		{
			static bool should_turn = true;
			
			if(std::time(nullptr) >= end_time)
			{
				should_turn = false;
			}
			if(should_turn)
			{
				_adc->_db->setSide(CONFIGS::MOTOR_SCALE, Side::Right);
				_adc->_db->setSide(-CONFIGS::MOTOR_SCALE, Side::Left);
			}
		}
		else if(degrees < 0) //counterclockwise
		{
			static bool should_turn = true;
			
			if(std::time(nullptr) >= end_time)
			{
				should_turn = false;
			}
			if(should_turn)
			{
				_adc->_db->setSide(-CONFIGS::MOTOR_SCALE, Side::Right);
				_adc->_db->setSide(CONFIGS::MOTOR_SCALE, Side::Left);
			}
		}
	}
};

AutoDriveController::AutoDriveController(DriveBase* db) : _db(db)
{

}

void AutoDriveController::run()
{
	//where all the auto commands go!
	//ex Robot.travel(12);
	//Robot.turn(50);
}
