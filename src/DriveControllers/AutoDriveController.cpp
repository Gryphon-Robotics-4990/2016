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
#include <iostream>
#include <cassert>

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
	std::vector<StatePackage> _sp;

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

		std::cout << end_time << std::endl;
		std::cout << std::time(nullptr) << std::endl;
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
		end_time += (_sp.size() == 0) ? 0 : _sp.end()->timeout;

		_sp.push_back({State::intake, end_time} );
	}

	void expell(double timeout)
	{
		std::time_t end_time = std::time(nullptr) + timeout;
		end_time += (_sp.size() == 0) ? 0 : _sp.end()->timeout;
		_sp.push_back({State::expell, end_time});
	}

	void noIntake(double timeout)
	{
		std::time_t end_time = std::time(nullptr) + timeout;
		end_time += (_sp.size() == 0) ? 0 : _sp.end()->timeout;

		_sp.push_back({State::none, end_time});

	}
	void update()
	{
		if(_cmds.empty() )
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
		}

		/*
		while(std::time(nullptr) > _sp[0].timeout)
		{
			std::cout << "Popping command with timeout " << _sp[0].timeout << std::endl;
			_sp.erase(_sp.begin() );
		}

		switch(_sp[0].state)
		{
			case State::intake:
				if(_adc->_in->pressed() )
				{
					_sp[0] = {State::none, _sp[0].timeout};
					break;
				}

				_adc->_in->setSpeed(CONFIGS::AUTO_SPEED);
				break;

			case State::expell:
				_adc->_in->setSpeed(-CONFIGS::AUTO_SPEED);
				break;

			case State::none:
				_adc->_in->setSpeed(0);
				break;

			default:
				break;
		}
		*/

		if(_cmds.empty() )
		{
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
	}
};

AutoDriveController::AutoDriveController(DriveBase* db, Fang* fng, Intake* in) : _db(db), _fng(fng), _in(in)
{
	rb = std::make_unique<Robot>(this);
	assert(rb);
	//run();
	_starttime = std::time(nullptr);
	_countdown.Start();
}

AutoDriveController::~AutoDriveController() = default;

void AutoDriveController::run()
{
	//where all the auto commands go!
	//ex rb->travel(12);
	//rb->turn(50);

	//five what? Nobody knows.
	rb->travel(10);
	//rb->turn(180);

	std::cout << "Loaded run commands" << std::endl;
}

void AutoDriveController::update()
{
	/*
	try
	{
		if(_starttime + 15 > std::time(nullptr) )
		{
			return;
		}

		std::cout << "a" << std::endl;
		rb->update();
		std::cout << "b" << std::endl;
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
//		throw e;
	}
	*/

	//for two seconds, turn the motor at the default auto speed

	//std::cout << _countdown.Get() << std::endl;
	if(_countdown.Get() < 4)
	{
		_db->setAll(CONFIGS::AUTO_SPEED);
	}
	else
	{
		//kill the motors
		_db->setAll(0);
	}
}
