//#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
//#include "motor.h"

class GPIOController
{
	//Motor* motor;
public:
	GPIOController();
	void doe_iets();
	void rij_naar_rechts();
	void bepaal_richting_snelheid_rupsbanden(int stickYrecieve, int stickXrecieve);
	void grijparm_besturing();
	void detecteer_objecten();
	void fillmotor();
	double get_axis_value() { return axis; };
	double get_value() { return sensorvalue; };
	double axis = 5.3;
	double sensorvalue = 2.7;
	std::list<std::string> get_motors() { return motors; };
	std::list<std::string> motors = { "Henk","Jan","Klaas","Piet","Joop","Wietse","Miel","Patrick", "Max", "Redmar" };
};
