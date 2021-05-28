#include "WebotsController.hpp"

// All the webots classes are defined in the "webots" namespace
using namespace webots;
WebotsController* controller = new WebotsController;

int main(int argc, char** argv) {
    //Wheels
    char wheels[2][20] = { "left wheel motor", "right wheel motor" };
    controller->SetMotorValues(&wheels[2][20]);
    controller->initdetect();


    return 0;
}