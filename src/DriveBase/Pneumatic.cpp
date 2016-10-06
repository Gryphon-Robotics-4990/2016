/*
 * Pnuematic.cpp
 *
 *  Created on: Oct 6, 2016
 *      Author: student
 */

#include <DriveBase/Pneumatic.h>

#include <Solenoid.h>

Pneumatic::Pneumatic(int pwmport) {
	// TODO Auto-generated constructor stub
	_sol = std::make_unique<Solenoid>(pwmport);
}

Pneumatic::~Pneumatic() = default;

void Pneumatic::toggle()
{
	_sol->Set(!_sol->Get() );
}

void Pneumatic::set(bool state)
{
	_sol->Set(state);
}

bool Pneumatic::state()
{
	return _sol->Get();
}
