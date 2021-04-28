#include <webots/Robot.hpp>
#include <webots/Keyboard.hpp>

// Added a new include file
#include <webots/Motor.hpp>

#define TIME_STEP 64
#define SPEED 0.5

#define MAX_SPEED 6.28

// All the webots classes are defined in the "webots" namespace
using namespace webots;

int main(int argc, char **argv) {
 Robot *robot = new Robot();

Keyboard keyboard;
keyboard.enable(TIME_STEP);

Motor *motor[10];

char wheels[10][16] = {"wheel_motor00","wheel_motor01","wheel_motor02",
  "wheel_motor03","wheel_motor04","wheel_motor05","wheel_motor06",
  "wheel_motor07","wheel_motor08","wheel_motor09"};
for(int i = 0; i < 10; i++){
  motor[i] =  robot->getMotor(wheels[i]);
  motor[i]->setVelocity(0.0);
}

for(int i = 0; i < 10; i++){
 motor[i]->setPosition(INFINITY);
 
}
 
 while (robot->step(TIME_STEP) != -1){
   int key=keyboard.getKey();
   //UP
    if (key==315){
      for(int i = 0; i < 10; i++){
        motor[i]->setVelocity(SPEED * MAX_SPEED);
      }
    key=keyboard.getKey();
    }
    //DOWN
    else if (key==317){
      for(int i = 0; i < 10; i++){
        motor[i]->setVelocity(-SPEED * MAX_SPEED);
      }
    key=keyboard.getKey();
   }
   //LEFT
    else if (key==316){
      for(int i = 0; i < 10; i++){
      if(i < 5){
        motor[i]->setVelocity(-SPEED * MAX_SPEED);
        }else
        motor[i]->setVelocity(SPEED * MAX_SPEED);
      }
    key=keyboard.getKey();
   }
   //RIGHT
   else if (key==314){
      for(int i = 0; i < 10; i++){
      if(i < 5){
        motor[i]->setVelocity(SPEED * MAX_SPEED);
        }else
        motor[i]->setVelocity(-SPEED * MAX_SPEED);
      }
    key=keyboard.getKey();
   }
   
   else{
    for(int i = 0; i < 10; i++){
      motor[i]->setVelocity(0.0);
    }
  }
 }

 delete robot;

 return 0;
}