/*
 * Pnuematic.h
 *
 *  Created on: Oct 6, 2016
 *      Author: student
 */

#ifndef SRC_DRIVEBASE_PNEUMATIC_H_
#define SRC_DRIVEBASE_PNEUMATIC_H_

#include <memory>

class Solenoid;

class Pneumatic {
private:
	std::unique_ptr<Solenoid> _sol;
public:
	Pneumatic(int pwmport);
	~Pneumatic();
	void toggle();
	void set(bool state);
	bool state();
};

#endif /* SRC_DRIVEBASE_PNEUMATIC_H_ */
