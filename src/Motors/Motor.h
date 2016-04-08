/*
 * Motor.h
 *
 *  Created on: Jan 22, 2016
 *      Author: norayu
 */

#ifndef SRC_MOTORS_MOTOR_H_
#define SRC_MOTORS_MOTOR_H_

#include <memory>

class TalonSRX;

class Motor
{
private:
	std::unique_ptr<TalonSRX> _motor;
	unsigned int _channel;
public:
	Motor(unsigned int channel);
	~Motor();
	void setSpeed(double speed);
	void kill();
	unsigned int getChannel() const;

};

#endif /* SRC_MOTORS_MOTOR_H_ */
