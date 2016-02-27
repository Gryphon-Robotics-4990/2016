/*
 * Fang.h
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

//based on intake 

#ifndef SRC_DRIVEBASE_FANG_H_
#define SRC_DRIVEBASE_FANG_H_

#include <memory>

class Motor;

class Fang
{
private:
	std::unique_ptr<Motor> _motor;
public:
	Fang(unsigned int port);
	~Fang();
	void setSpeed(double speed);
	void force(double speed);
};

#endif /* SRC_DRIVEBASE_FANG_H_ */
