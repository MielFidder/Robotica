#include "ControllerFacade.h"


ControllerFacade::ControllerFacade()
{
	//controller = new WebotsController();
	controller = new GPIOController();
}

void ControllerFacade::bepaal_richting_snelheid_rupsbanden(int stickYreceive, int stickXreceive)
{
	controller->bepaal_richting_snelheid_rupsbanden(stickYreceive, stickXreceive);
}
