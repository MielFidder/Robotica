#include "Webotscontroller.hpp"
#include <iostream>

using namespace webots;
class Facade {
 protected:
	 WebotsController* webotscontroller_;
public:
	Facade(
		WebotsController* webotscontroller = nullptr) {
		this->webotscontroller_ = webotscontroller;
	}
	~Facade() {
		delete webotscontroller_;
	}
	void Operation(std::string text, char wheels[], double right, double left, int axis);
};
