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

class Intake;
class Gamepad;
class HallEffectSensor;

class FangControl
{
private:
	Fang* _fn;
	HallEffectSensor* _hs;
	Gamepad* _gp;

 //defaults to .5
	void up(double speed = .5);
	void down(double speed = .5);
public:
	FangControl(Fang* fn, HallEffectSensor* hs, Gamepad* gp);
	~FangControl();

	void update();
};

#endif /* SRC_EXTRACONTROLLERS_FANGCONTROL_H_ */
