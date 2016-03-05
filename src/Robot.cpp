#include "WPILib.h"

#include "DriveBase/DriveBase.h"
#include "Motors/Motor.h"
#include "DriveControllers/TeleopDrivetrainController.h"
#include "DriveControllers/AutoDriveController.h"
#include "Controllers/Gamepad.h"
#include "ExtraControllers/IntakeControl.h"
#include "DriveBase/Intake.h"
#include "Sensors/LimitSwitch.h"
#include "DriveBase/Fang.h"
#include "ExtraControllers/FangControl.h"
#include "Sensors/HallEffectSensor.h"

#include <memory>

class Robot: public IterativeRobot
{
private:
	//Probably have a Union of Teleop and Auto DC later
	std::unique_ptr<TeleopDrivetrainController> tdtc;
	std::unique_ptr<AutoDriveController> adc;

	std::unique_ptr<IntakeControl> ic;
	std::unique_ptr<FangControl> fc;


	DriveBase db {
			//set the values later
			0, Side::Right,
			3, Side::Right,
			5, Side::Right,
			4, Side::Left,
			2, Side::Left,
			7, Side::Left
	};

	//There is no LimitSwitch
	LimitSwitch ball_seek{0};

	//port num -v
	Intake in {6, &ball_seek};

	//dummy value right now
	Fang fng {1};

	std::unique_ptr<HallEffectSensor> hes_arr[3] =
	{
			std::make_unique<HallEffectSensor>(0),
			std::make_unique<HallEffectSensor>(1),
			std::make_unique<HallEffectSensor>(2)
	};

	//number is the usb port of the controller according to the driver station
	Gamepad gp{0};

	void RobotInit()
	{
		ic = std::make_unique<IntakeControl>(&in, &gp);
		fc = std::make_unique<FangControl>(&fng, hes_arr[0].get(), hes_arr[1].get(), hes_arr[2].get(), &gp);
	}

	/**
     * This function is called once each time the robot enters Disabled mode.
     * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
     */
	void DisabledInit()
	{

	}

	void DisabledPeriodic()
	{
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString code to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional commands to the chooser code above (like the commented example)
	 * or additional comparisons to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit()
	{
		adc = std::make_unique<AutoDriveController>(&db, &fng, &in);
	}

	void AutonomousPeriodic()
	{
		adc->update();
	}

	void TeleopInit()
	{
		tdtc = std::make_unique<TeleopDrivetrainController>(&db, &gp);
	}

	void TeleopPeriodic()
	{
		tdtc->update();
		ic->update();
		fc->update();
	}

	void TestPeriodic()
	{

	}
};

START_ROBOT_CLASS(Robot)

