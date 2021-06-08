#include <webots/Robot.hpp>
#include <webots/Joystick.hpp>
// Added a new include file
#include <webots/Motor.hpp>
#include <webots/Keyboard.hpp>
#include <webots/LED.hpp>

#include <iostream>
#include <iosfwd>
#include <fstream>

#define TIME_STEP 64
#define SPEEDMULT 2500

// All the webots classes are defined in the "webots" namespace
using namespace webots;

bool danceMode = false;
bool LEDmode = false;
bool isRecording = false;
int steps = 0;

int defaultM = 12;
double defaultSpeed = 11.55;
std::vector<std::vector<double>> queue;
std::vector<std::vector<double>> recording;
std::vector<int> FQ;

//Hoever wil ik rijden
double calculateDistance(double distance){
    return distance * defaultM;
}

//Rotate in aangegeven graden
void Rotate(int graden){
  int rotate = std::ceil(graden / 10);
    for(int i = 0; i < rotate; i++){
    std::vector<double> temp = {defaultSpeed, -defaultSpeed};
    queue.push_back(temp);
  }
}

//split dance file lines
std::vector<double> BreakLines(std::string line){
  int commaPos = line.find(",");
  
  std::string partOne = line.substr(0,commaPos);
  std::string partTwo = line.substr(commaPos+1,line.size()-1);
  std::string::size_type sz;
  
  double pone = std::stod(partOne, &sz);
  double ptwo = std::stod(partTwo, &sz);
  
  std::vector<double> temp = {pone, ptwo};
    
  return temp;
}

//Load dance file
void LoadStepFile(std::string url){
  std::ifstream myFile(url);
  
  if(myFile.is_open()){
    std::string line;

    while(getline(myFile, line)){
          //std::cout<<line<<std::endl;
      queue.push_back(BreakLines(line));
      
    }
    myFile.close();
  }else{
    std::cout<<"File not found"<<std::endl;
  }

}

//Set up dance queue
void DanceQueue(){
   std::cout<<"Loading queue"<<std::endl;
   LoadStepFile("queue.txt");
}

//Fill Frequency queue //zou nog gecombineerd kunnen worden met danceQueue
void FillFQ(){
  for(int i = 0; i < 50; i++){
    for(int i = 0; i < 5; i++){
      FQ.push_back(1);
    }
    
    for(int i = 0; i < 15; i++){
      FQ.push_back(2);
    }
    
    for(int i = 0; i < 10; i++){
      FQ.push_back(3);
    }
  }
  std::cout<<"Done"<<std::endl;
}

//FQ:
// Low: < 200
// Med: - 2k
// HIH: 2k >


//Main
int main(int argc, char **argv) {
 Robot *robot = new Robot();

  Joystick joystick;
  joystick.enable(TIME_STEP);
  
  Keyboard keyboard;
  keyboard.enable(TIME_STEP);
  
  //Motors setten -----------------------
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
  //--------------------------------------
  
  //Leds setten --------------------------
  LED *led[1];
  
  char leds[1][6] = {"led"};
  
  for(int i = 0; i < 1; i++){
    led[i] = robot->getLED(leds[i]);
  }
  //--------------------------------------
  
  //Zorg dat er wat is geschreven naar de file en kijk of het werkt
  std::ofstream myFile;

  FillFQ(); 

  while (robot->step(TIME_STEP) != -1){
  
    int key = keyboard.getKey();
    int recordKey = 82; // R
    int danceKey = 68; // D
    int ledKey = 76; // L
    //std::cout<<key<<std::endl;
    
    //Proces key press
    if(key == recordKey){
      _sleep(100);
      isRecording = !isRecording;
      if(isRecording){
        myFile.open("queue.txt", std::ios::out|std::ios::app);;
      }
    }
    
    if(key == danceKey){
      _sleep(100);
      danceMode = !danceMode;
      if(danceMode){
        //std::cout<<"mode :"<<danceMode<<std::endl;
        DanceQueue();
      }
    }
    
    if(key == ledKey){
      _sleep(100);
      LEDmode = !LEDmode;
    }
  
    //Als het geen danceMode is dan kun je zelf sturen
    if(!danceMode){
      double stickX = joystick.getAxisValue(1);
      double stickY = joystick.getAxisValue(0);
      
      double stickYinv = (0-stickY)/SPEEDMULT;
      double stickXinv = (0-stickX)/SPEEDMULT;
      
      double v = (100 - abs(stickXinv)) * (stickYinv/100) + stickYinv;
      double w = (100 - abs(stickYinv)) * (stickXinv/100) + stickXinv;
       
      double l = (v-w)/2;
      double r = (v+w)/2;
     
      if(l > -1 && l < 1){
        l = 0;
      }
      if(r > -1 && r < 1){
         r = 0;
      }
  
      std::vector<double> temp = {l,r};
      queue.push_back(temp);
    }
    if(LEDmode){
      if(FQ[0] == 1){
        for(int i = 0; i < 10; i++){
          if(i < 5){
            motor[i]->setVelocity(-defaultSpeed);
          }else{
            motor[i]->setVelocity(-defaultSpeed);
          }
        }
      }
      if(FQ[0] == 2){
        for(int i = 0; i < 10; i++){
          if(i < 5){
            motor[i]->setVelocity(defaultSpeed);
          }else{
            motor[i]->setVelocity(defaultSpeed);
          }
        }
      }
      if(FQ[0] == 3){
        for(int i = 0; i < 10; i++){
          if(i < 5){
            motor[i]->setVelocity(defaultSpeed);
          }else{
            motor[i]->setVelocity(-defaultSpeed);
          }
        }
      }
      
      for(int i = 0; i < 1; i++){
        led[i]->set(FQ[0]);
      }
         
      FQ.erase(FQ.begin());
      std::cout<<FQ.size()<<std::endl;
    }
  
    if(!LEDmode){
      if(queue.size() != 0){
        for(int i = 0; i < 10; i++){
          if(i < 5){
            motor[i]->setVelocity(queue[queue.size()-1][1]);
          }else{
            motor[i]->setVelocity(queue[queue.size()-1][0]);
          }
        }
        if(!danceMode && isRecording){
          std::vector<double> temp = {queue[queue.size()-1][0], queue[queue.size()-1][1]};
          recording.push_back(temp);
        }
         queue.erase(queue.end()-1);
      }
      
      if(recording.size() != 0 && !isRecording){
        for (int i = 0; i < recording.size(); i++){
          myFile << recording[i][1] << ","<< recording[i][0] << "\n";
        }
      }
    }
  }

  std::cout<<"File Closed"<<std::endl;
  myFile.close();
  
 delete robot;

 return 0;
}

