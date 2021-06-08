#pragma once
#include "WebotsController.h"
#include "GPIOController.h"

class ControllerFacade
{
	//WebotsController* controller;
	GPIOController* controller;
public:
	ControllerFacade();
	void bepaal_richting_snelheid_rupsbanden(int stickYreceive, int stickXreceive);
};

