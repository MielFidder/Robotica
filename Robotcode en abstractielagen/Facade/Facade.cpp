#include "Facade.hpp"

using namespace webots;
void Facade::Operation(std::string text, char wheels[], double right, double left, int axis){
	this->webotscontroller_->SetMotorValues(wheels);
	this->webotscontroller_->initarm();
	this->webotscontroller_->initdetect();
	this->webotscontroller_->SetWheelVelocity(right, left);
	this->webotscontroller_->JoystickOperation(axis);
	this->webotscontroller_->GeeftTextWeer(text);
}