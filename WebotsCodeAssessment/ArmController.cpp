#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Joystick.hpp>

// All the webots classes are defined in the "webots" namespace
using namespace webots;
#define TIME_STEP 64
#define SPEEDMULTARM 15000
#define SPEEDMULTGRIP 35000

int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();  
  Motor *motor[8];
  
  Joystick joystick;
  joystick.enable(TIME_STEP);
  
  char wheelMotors[8][8] = {"1", "2", "3", "4", "5", "6", "7", "7 left"};
  for(int i = 0; i < 8; i++){
    motor[i] = robot->getMotor(wheelMotors[i]);
    motor[i]->setVelocity(0.0);
    motor[i]->setPosition(INFINITY);
  }
  
  motor[6]->setPosition(INFINITY);
  

    
    
  while (robot->step(TIME_STEP) != -1) {
    // 1 & 2 moeten blijven staan
    // 7 & 7 left zijn grijper
    // 3 & 5 voor en achter
    // 4 & 6 rotaties
    //alles -1 voor index
    
    //velocity
    double stickX = joystick.getAxisValue(1);
    double stickY = joystick.getAxisValue(0);
    
    double stick2X = joystick.getAxisValue(2);
    double stick2Y = joystick.getAxisValue(3);
    
    double stickYpower = stickY / SPEEDMULTARM;
    double stickXpower = 0 - (stickX / SPEEDMULTARM);
    
    double stick2Ypower = stick2Y / SPEEDMULTGRIP;
    double stick2Xpower = 0 - (stick2X / SPEEDMULTGRIP);
        

    //std::cout<< "y: "<< stick2Ypower <<std::endl;
    //std::cout<< "x: "<< stick2Xpower <<std::endl;
    
    //std::cout<< "x: "<< motor[6]->getTorqueFeedback() <<std::endl;
   
   //Check voor als de stick niet aangeraakt wordt 
    if(stickYpower < 1.2 && stickYpower > -1.2)
      motor[4]->setVelocity(0.0);
    else
      motor[4]->setVelocity(stickYpower);
    
    if(stickXpower < 1.2 && stickXpower > -1.2)
      motor[3]->setVelocity(0.0);
    else
      motor[3]->setVelocity(stickXpower);
      
    if(stick2Ypower < 0.3 && stick2Ypower > -0.3){
        motor[6]->setVelocity(0.0);
        motor[7]->setVelocity(0.0);
     }else{
        motor[6]->setVelocity(stick2Ypower);
        motor[7]->setVelocity(stick2Ypower);
     }
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
