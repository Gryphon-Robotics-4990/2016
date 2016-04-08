/*
 * LimitSwitch.h
 *
 *  Created on: Feb 22, 2016
 *      Author: user
 */

#ifndef SRC_SENSORS_LIMITSWITCH_H_
#define SRC_SENSORS_LIMITSWITCH_H_

#include <memory>

class DigitalInput;

//interface
//may have to change if the loop isn't fast enough
class LimitSwitch
{
private:
	unsigned int _port;
	std::unique_ptr<DigitalInput> _switch;

public:
	LimitSwitch(unsigned int port);
	~LimitSwitch();
	bool pressed();
};

#endif /* SRC_SENSORS_LIMITSWITCH_H_ */
