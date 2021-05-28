#include "Facade.hpp"

//define key codes



// All the webots classes are defined in the "webots" namespace
using namespace webots;
WebotsController* controller = new WebotsController;

int main(int argc, char** argv) {
    char wheelMotors[10][16] = { "wheel_motor00","wheel_motor01","wheel_motor02",
            "wheel_motor03","wheel_motor04","wheel_motor05","wheel_motor06",
            "wheel_motor07","wheel_motor08","wheel_motor09" };
    controller->SetMotorValues(&wheelMotors[10][16]);
    return 0;
}

void JoystickControls() {
    int stickX = controller->JoystickOperation(1);
    int stickY = controller->JoystickOperation(0);

    int speedMult = 1500;

    int stickYinv = (0 - stickY) / speedMult;
    int stickXinv = (0 - stickX) / speedMult;

    int v = (100 - abs(stickXinv)) * (stickYinv / 100) + stickYinv;
    int w = (100 - abs(stickYinv)) * (stickXinv / 100) + stickXinv;

    int l = (v - w) / 2;
    int r = (v + w) / 2;

    std::cout << "R: " << r << std::endl;


    controller->SetWheelVelocity(r, l);
}

void KeyPres() {

}