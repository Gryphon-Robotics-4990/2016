/*
 * AutoDriveController.cpp
 *
 *  Created on: Feb 13, 2016
 *      Author: user
 */

#include <DriveControllers/AutoDriveController.h>

#include "DriveBase/DriveBase.h"
#include "Configs/CONFIGS.h"

#include <cmath>
#include <ctime>
#include <vector>

enum class Commands
{
	travel_f,
	travel_b,
	turn_c,
	turn_cc
};

struct CommandPackage
{
	Commands cmd;
	std::time_t endtime;
};


class AutoDriveController::Robot
{
private:
	AutoDriveController* const _adc;

	std::vector<CommandPackage> _cmds;
public:
	Robot(AutoDriveController* adc) : _adc(adc){};

	//class to have all of the robot command binds!
	void travel(double metres)
	{
		//implement!
		//no encoders so we have to guess :(

		//assuming time_t is seconds
		std::time_t end_time = std::time(nullptr) + (std::abs(metres) / CONFIGS::MAX_SPEED);

		if(metres > 0)
		{
			_cmds.push_back({Commands::travel_f, end_time});
		}
		else if(metres < 0)
		{
			_cmds.push_back({Commands::travel_b, end_time});
		}
	}

	//clockwise
	void turn(double degrees)
	{
		//assuming degrees!
		constexpr int deg_in_circle = 360;
		double distance = (CONFIGS::ROBOT_WIDTH * M_PI * degrees) / deg_in_circle;

		constexpr char double_motors = 2;
		std::time_ts end_time = std::time(nullptr) + (std::abs(distance) / CONFIGS::MAX_SPEED * double_motors);

		if(degrees > 0)
		{
			_cmds.push_back({Commands::turn_c, end_time});
		}
		else if(degrees < 0)
		{
			_cmds.push_back({Commands::turn_cc, end_time});
		}
	}

	void update()
	{
		while(true)
		{
			if(_cmds[0].endtime > std::time(nullptr) )
			{
				break;
			}

			constexpr char DEAD = 0;
			_adc->_db->setAll(DEAD);
		}

		switch(_cmds[0].cmd)
		{
			case Commands::travel_f:
				_adc->_db->setAll(CONFIGS::MOTOR_SCALE);
				break;

			case Commands::travel_b:
				_adc->_db->setAll(-CONFIGS::MOTOR_SCALE);
				break;

			case Commands::turn_c:
				_adc->_db->setSide(CONFIGS::MOTOR_SCALE, Side::Right);
				_adc->_db->setSide(-CONFIGS::MOTOR_SCALE, Side::Left);
				break;

			case Commands::turn_cc:
				_adc->_db->setSide(-CONFIGS::MOTOR_SCALE, Side::Right);
				_adc->_db->setSide(CONFIGS::MOTOR_SCALE, Side::Left);
				break;

			default:
				break;
		}
	}
};

AutoDriveController::AutoDriveController(DriveBase* db) : _db(db)
{
	rb = std::make_unique<Robot>(this);
	run();
}

AutoDriveController::~AutoDriveController() = default;

void AutoDriveController::run()
{
	//where all the auto commands go!
	//ex rb->travel(12);
	//rb->turn(50);
}

void AutoDriveController::update()
{
	rb->update();
}
