/*
 * HallEffectSensor.h
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

//literally the exact same thing as a limit switch

#ifndef SRC_SENSORS_HALLEFFECTSENSOR_H_
#define SRC_SENSORS_HALLEFFECTSENSOR_H_

#include <memory>

class DigitalInput;

//interface
//may have to change if the loop isn't fast enough
class HallEffectSensor
{
private:
	unsigned int _port;
	std::unique_ptr<DigitalInput> _switch;

public:
	HallEffectSensor(unsigned int port);
	~HallEffectSensor();
	bool pressed();
};

#endif /* SRC_SENSORS_HALLEFFECTSENSOR_H_ */
