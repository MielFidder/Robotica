#include "Facade.hpp"
using namespace webots;
WebotsController* controller = new WebotsController;
void VulText() {
	std::string text = "Dit wil ik graag geprint hebben";
	controller->GeeftTextWeer(text);
}