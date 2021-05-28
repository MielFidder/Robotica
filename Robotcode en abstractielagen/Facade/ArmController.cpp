#include "WebotsController.hpp"

// All the webots classes are defined in the "webots" namespace
using namespace webots;
WebotsController* controller = new WebotsController;

int main(int argc, char** argv) {
    // create the Robot instance.
    char wheelMotors[8][8] = { "1", "2", "3", "4", "5", "6", "7", "8" };
    controller->initarm();
    controller->SetMotorValues(&wheelMotors[8][8]);
  };