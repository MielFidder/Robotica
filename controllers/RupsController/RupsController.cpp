#include <webots/Robot.hpp>
#include <webots/Joystick.hpp>

// Added a new include file
#include <webots/Motor.hpp>

#define TIME_STEP 64
#define SPEEDMULT 1500

// All the webots classes are defined in the "webots" namespace
using namespace webots;

bool danceMode = false;

void Dance(){
   std::cout<<"Dance"<<std::endl;
}

int main(int argc, char **argv) {
 Robot *robot = new Robot();

Joystick joystick;
joystick.enable(TIME_STEP);

Motor *motor[10];

char wheelMotors[10][16] = {"wheel_motor00","wheel_motor01","wheel_motor02",
  "wheel_motor03","wheel_motor04","wheel_motor05","wheel_motor06",
  "wheel_motor07","wheel_motor08","wheel_motor09"};
for(int i = 0; i < 10; i++){
  motor[i] = robot->getMotor(wheelMotors[i]);
  motor[i]->setVelocity(0.0);
}

for(int i = 0; i < 10; i++){
 motor[i]->setPosition(INFINITY);
 
}

 while (robot->step(TIME_STEP) != -1){
   
   if(danceMode == true){
     Dance();
   }else{
     int stickX = joystick.getAxisValue(1);
     int stickY = joystick.getAxisValue(0);
    
     int stickYinv = (0-stickY)/SPEEDMULT;
     int stickXinv = (0-stickX)/SPEEDMULT;
  
     int v = (100 - abs(stickXinv)) * (stickYinv/100) + stickYinv;
     int w = (100 - abs(stickYinv)) * (stickXinv/100) + stickXinv;
     
     int l = (v-w)/2;
     int r = (v+w)/2;
  
     //std::cout<<"L: " <<l<<std::endl;
     //std::cout<<"R: " <<r<<std::endl;
     
    
    for(int i = 0; i < 10; i++){
      if(i < 5)
        motor[i]->setVelocity(r);
      else
        motor[i]->setVelocity(l);
     }
   }
 }

 delete robot;

 return 0;
}

