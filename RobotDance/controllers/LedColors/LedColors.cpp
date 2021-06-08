#include <webots/Robot.hpp>
#include <webots/LED.hpp>
#include <webots/Radar.hpp>

#define TIME_STEP 64

// All the webots classes are defined in the "webots" namespace
using namespace webots;


int main(int argc, char **argv) {
  Robot *robot = new Robot();
 
  
  LED *led[1];
  
  char leds[1][6] = {"led"};
  
  for(int i = 0; i < 1; i++){
    led[i] = robot->getLED(leds[i]);
  }
  
  while (robot->step(TIME_STEP) != -1) {
    
    for(int i = 0; i < 1; i++){
      led[i]->set(3);
    }
    
  };
  
  // Enter here exit cleanup code.
  
  delete robot;
  return 0;
}
