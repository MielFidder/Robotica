#include "GPIOController.h"
#include "pipe.cpp"
int inA1 = 24; // DCmotor A
int inA2 = 28; // DCmotor A
int inB1 = 29; // DCmotor B
int inB2 = 25; // DCmotor B
int pwm1 = 26; // pwn pin 1 Hoe snel wil je gaan?
int pwm2 = 23; // pwn pin 2 

GPIOController::GPIOController(){
}
void GPIOController::bepaal_richting_snelheid_rupsbanden(int stickYreceive, int stickXreceive)
{
	int stickX = stickXreceive;
	int stickY = stickYreceive;
	double stickYinv = (0 - stickY);
	double stickXinv = (0 - stickX);

	double v = (100 - abs(stickXinv)) * (stickYinv / 100) + stickYinv;
	double w = (100 - abs(stickYinv)) * (stickXinv / 100) + stickXinv;

	int l = (v - w) / 2;
	int r = (v + w) / 2;
	
	if (l > -65 && l < 20)
		l = 0;
	
	if (r > -65 && r < 20)
		r = 0;
	
	
	int powerA1 = 0; //low energy, geen stroom naartoe
	int powerA2 = 0; // 0 = low, 1 = high
	int powerB1 = 0;
	int powerB2 = 0;
	
	if (l > 0){
		powerA1 = 1;
		powerA2 = 0;
	}else{
		powerA1 = 0;
		powerA2 = 1;
	}
	if(r > 0){
		powerB1 = 1;
		powerB2 = 0;
	}else{
		powerB1 = 0;
		powerB2 = 1;
	}
	
	l = std::abs(l);
	r = std::abs(r);
	
	std::vector<int> values = {l, r, powerA1, powerA2, powerB1, powerB2};
	
	for(int i = 2; i < values.size(); i++){
		if(values[i] > 0)
			digitalWrite(drivePins[i], HIGH); 
		else
			digitalWrite(drivePins[i], LOW); 
	}
	
	//Zet de snelheid van de motors
	digitalWrite(pwm1, values[0]); // l
	digitalWrite(pwm2, values[1]); // r
}
