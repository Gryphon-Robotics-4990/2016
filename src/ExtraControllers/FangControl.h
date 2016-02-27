/*
 * FangControl.h
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

//pretty much the same thing as intake 

#ifndef SRC_EXTRACONTROLLERS_FANGCONTROL_H_
#define SRC_EXTRACONTROLLERS_FANGCONTROL_H_

#include <memory>

class Fang;
class Gamepad;
class HallEffectSensor;

class FangControl
{
private:
	Fang* _fn;
	HallEffectSensor* _hs[3];
	Gamepad* _gp;

 //defaults to .5
	void up();
	void down();
	void force(double speed);
public:
	FangControl(Fang* fn, HallEffectSensor* hs[], Gamepad* gp);
	~FangControl();

	void update();
};

#endif /* SRC_EXTRACONTROLLERS_FANGCONTROL_H_ */
