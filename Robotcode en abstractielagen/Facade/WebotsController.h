#include "Types.h"
#include "Device.hpp"
#include "Motor.hpp"
#include "Joystick.hpp"
#include "Robot.hpp"
#include "DistanceSensor.hpp"
#include "Keyboard.hpp"
#define TIME_STEP 64
#define SPEEDMULTARM 15000
#define SPEEDMULTGRIP 35000
#define TIME_STEP 64
#define SPEED 1
#define MAX_SPEED 6.28
namespace webots {
    class WebotsController {
    public:
        Motor* motor_;
        Joystick* joystick_;
        Robot* robot_;
        Keyboard* keyboard_;
        Motor* rbmotoren[10];
        Motor* armmotoren[8];
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
    };
}
