#ifndef SRC_CONFIGS_CONFIGS_H_
#define SRC_CONFIGS_CONFIGS_H_

namespace CONFIGS {
	//in m/s
	constexpr double MAX_SPEED = 2.7432;

	//so the robot doesn't go max speed
	constexpr double MOTOR_SCALE = .85;

	//accel time in ms
	constexpr double ACCEL_TIME = 175.0;

	constexpr double THROTTLE_CUTOFF = .0006;

	constexpr double MAX_TURN_RADIUS = 1.0;

	//scale for intake motor
	constexpr double INTAKE_SCALE = 1;
	//robot width in m
	constexpr double ROBOT_WIDTH = .86;

	//binds for intake
	constexpr unsigned int LT_BIND = 2;
	constexpr unsigned int RT_BIND = 3;
	constexpr unsigned int RB_BIND = 6;
	//compensation for right trigger dead spot
	constexpr float RT_COMP = 0;

	//compensation for left trigger dead spot
	constexpr float LT_COMP = 0;

	constexpr char START_FANG_POS = 0;

	//default speed of intake motor and fang
	constexpr double DEF_SPEED = .8;

	constexpr double AUTO_SPEED = .5 * MOTOR_SCALE;

	//drive beta
	constexpr bool DRIVE_BETA = false;
}

#endif /* SRC_CONFIGS_CONFIGS_H_ */
