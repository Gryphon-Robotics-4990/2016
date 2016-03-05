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
class HallEffectSensor;

class Fang
{
public:
	static constexpr unsigned char MAX_POS = 3;
private:
	std::unique_ptr<Motor> _motor;

	HallEffectSensor* _hs[MAX_POS];
public:

	Fang(unsigned int port, HallEffectSensor* hsa, HallEffectSensor* hsb, HallEffectSensor* hsc);
	~Fang();
	void setSpeed(double speed);
	void force(double speed);
	HallEffectSensor* getSensor(unsigned char pos);
};

#endif /* SRC_DRIVEBASE_FANG_H_ */
