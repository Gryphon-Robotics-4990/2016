/*
 * AutoDriveController.cpp
 *
 *  Created on: Feb 13, 2016
 *      Author: user
 */

#include <DriveControllers/AutoDriveController.h>

#include "DriveBase/DriveBase.h"
#include "Configs/CONFIGS.h"
#include "DriveBase/Intake.h"
#include "DriveBase/Fang.h"

#include <cmath>
#include <ctime>
#include <vector>

//ASSUMES std::time_t IS IN SECONDS

enum class Commands
{
	travel_f,
	travel_b,
	turn_c,
	turn_cc,
	wait,
};

enum class State
{
	none,
	intake,
	expell,
};

struct CommandPackage
{
	Commands cmd;
	std::time_t endtime;
};

struct StatePackage
{
	State state;
	std::time_t timeout;
};


class AutoDriveController::Robot
{
private:
	AutoDriveController* const _adc;

	std::vector<CommandPackage> _cmds;
	StatePackage _sp;

public:
	Robot(AutoDriveController* adc) : _adc(adc){};

	//class to have all of the robot command binds!
	void travel(double metres)
	{
		//implement!
		//no encoders so we have to guess :(

		//assuming time_t is seconds
		std::time_t end_time = ((_cmds.size() == 0) ? std::time(nullptr) : _cmds.end()->endtime) + (std::abs(metres) / CONFIGS::MAX_SPEED);

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
		std::time_t end_time = ((_cmds.size() == 0) ? std::time(nullptr) : _cmds.end()->endtime) + (std::abs(distance) / CONFIGS::MAX_SPEED * double_motors);

		if(degrees > 0)
		{
			_cmds.push_back({Commands::turn_c, end_time});
		}
		else if(degrees < 0)
		{
			_cmds.push_back({Commands::turn_cc, end_time});
		}
	}

	void wait(double seconds)
	{
		std::time_t end_time = ((_cmds.size() == 0) ? std::time(nullptr) : _cmds.end()->endtime) + seconds;
		_cmds.push_back({Commands::wait, end_time});
	}

	void intake(double timeout)
	{
		std::time_t end_time = std::time(nullptr) + timeout;
		_sp = {State::intake, end_time};
	}

	void expell(double timeout)
	{
		std::time_t end_time = std::time(nullptr) + timeout;
		_sp = {State::expell, end_time};
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

			//pop off first command
			_cmds.erase(_cmds.begin() );
		}

		if(std::time(nullptr) > _sp.timeout)
		{
			_sp = {State::none, -1};
		}

		switch(_sp.state)
		{
			case State::intake:
				if(_adc->_in->pressed() )
				{
					_sp = {State::none, -1};
					break;
				}

				_adc->_in->setSpeed(CONFIGS::AUTO_SPEED);
				break;

			case State::expell:
				_adc->_in->setSpeed(CONFIGS::AUTO_SPEED);
				break;

			default:
				break;
		}

		switch(_cmds[0].cmd)
		{
			case Commands::travel_f:
				_adc->_db->setAll(CONFIGS::AUTO_SPEED);
				break;

			case Commands::travel_b:
				_adc->_db->setAll(-CONFIGS::AUTO_SPEED);
				break;

			case Commands::turn_c:
				_adc->_db->setSide(CONFIGS::AUTO_SPEED, Side::Right);
				_adc->_db->setSide(-CONFIGS::AUTO_SPEED, Side::Left);
				break;

			case Commands::turn_cc:
				_adc->_db->setSide(-CONFIGS::AUTO_SPEED, Side::Right);
				_adc->_db->setSide(CONFIGS::AUTO_SPEED, Side::Left);
				break;

			case Commands::wait:
				break;

			default:
				break;
		}
	}
};

AutoDriveController::AutoDriveController(DriveBase* db, Fang* fng, Intake* in) : _db(db), _fng(fng), _in(in)
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
