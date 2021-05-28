#include "Types.h"
#include "Device.hpp"
#include "Motor.hpp"
#include "Joystick.hpp"
#include "Robot.hpp"
#include "DistanceSensor.hpp"
#include "Keyboard.hpp"
#include <iostream>
namespace webots {
	class WebotsController {
	protected:
		Motor* motor_;
		Joystick* joystick_;
		Robot* robot_;
		Keyboard* keyboard_;
		Motor* rbmotoren[10];
		Motor* armmotoren[8];
	public:
		WebotsController(
			Motor* motor = nullptr,
			Joystick* joystick = nullptr,
			Robot* robot = nullptr,
			Keyboard* keyboard = nullptr) {
			this->motor_ = motor;
			this->joystick_ = joystick;
			this->robot_ = robot;
			this->keyboard_ = keyboard;
		}
		~WebotsController() {
			delete motor_;
			delete joystick_;
			delete robot_;
			delete keyboard_;
		}
		void SetMotorValues(char wheels[]);
		void initarm();
		void initdetect();
		void SetWheelVelocity(double right, double left);
		int JoystickOperation(int axis);
	};
}