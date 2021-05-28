#include "Types.h"
#include "Device.hpp"
#include "Motor.hpp"
#include "Joystick.hpp"
#include "Robot.hpp"
#include "DistanceSensor.hpp"
#include "Keyboard.hpp"
#define TIME_STEP 64
#define SPEEDMULTARM 15000
#define SPEEDMULTGRIP 35000
#define TIME_STEP 64
#define SPEED 1
#define MAX_SPEED 6.28
namespace webots {
	class WebotsController {
	protected:
		Motor* motor_;
		Joystick* joystick_;
		Robot* robot_;
        Keyboard* keyboard_;
		Motor* rbmotoren[10];
		Motor* armmotoren[8];
	public:
		WebotsController(
			Motor* motor = nullptr,
			Joystick* joystick = nullptr,
			Robot* robot = nullptr,
            Keyboard* keyboard = nullptr){
			this->motor_ = motor;
			this->joystick_ = joystick;
			this->robot_ = robot;
            this->keyboard_ = keyboard;
		}
		~WebotsController() {
			delete motor_;
			delete joystick_;
			delete robot_;
            delete keyboard_;
		}
		void SetMotorValues(char wheels[]) {
			for (int i = 0; i < 10; i++) {
				std::string wielmotor(16,wheels[i]);
				rbmotoren[i] = robot_->getMotor(wielmotor);
				rbmotoren[i]->setVelocity(0.0);
				rbmotoren[i]->setPosition(INFINITY);
			}
		}

		void initarm() {
			joystick_->enable(TIME_STEP);
			armmotoren[6]->setPosition(INFINITY);

			while (robot_->step(TIME_STEP) != -1) {
				// 1 & 2 moeten blijven staan
				// 7 & 7 left zijn grijper
				// 3 & 5 voor en achter
				// 4 & 6 rotaties
				//alles -1 voor index

				//velocity
				double stickX = joystick_->getAxisValue(1);
				double stickY = joystick_->getAxisValue(0);

				double stick2X = joystick_->getAxisValue(2);
				double stick2Y = joystick_->getAxisValue(3);

				double stickYpower = stickY / SPEEDMULTARM;
				double stickXpower = 0 - (stickX / SPEEDMULTARM);

				double stick2Ypower = stick2Y / SPEEDMULTGRIP;
				double stick2Xpower = 0 - (stick2X / SPEEDMULTGRIP);


				//std::cout<< "y: "<< stick2Ypower <<std::endl;
				//std::cout<< "x: "<< stick2Xpower <<std::endl;

				std::cout << "x: " << armmotoren[6]->getTorqueFeedback() << std::endl;


				if (stickYpower < 1.2 && stickYpower > -1.2)
					armmotoren[4]->setVelocity(0.0);
				else
					armmotoren[4]->setVelocity(stickYpower);

				if (stickXpower < 1.2 && stickXpower > -1.2)
					armmotoren[3]->setVelocity(0.0);
				else
					armmotoren[3]->setVelocity(stickXpower);

				if (stick2Ypower < 0.3 && stick2Ypower > -0.3) {
					armmotoren[6]->setVelocity(0.0);
					armmotoren[7]->setVelocity(0.0);
				}
				else {
					armmotoren[6]->setVelocity(stick2Ypower);
					armmotoren[7]->setVelocity(stick2Ypower);
				}
			};
		}

		void initdetect() {
            DistanceSensor* ds[3];
            char dsNames[3][5] = {
              "ds0", "ds2", "ds13"
            };
            for (int i = 0; i < 3; i++) {
                ds[i] = robot_->getDistanceSensor(dsNames[i]);
                ds[i]->enable(TIME_STEP);
            }
            //read sensors outputs 
            double dsValues[3];
            for (int i = 0; i < 3; i++) {
                dsValues[i] = ds[i]->getValue();
                //std::cout<<"v: " << dsValues[i]<<std::endl;
            }

            int key = keyboard_->getKey();
            int key2 = keyboard_->getKey();
            int combine = key + key2;


            //up
            if (key == 315) {
                if (dsValues[0] > 60) {
                    //for(int i = 0; i < 2; i++){
                      //motor[i]->setVelocity(0.0);
                    //}
                    //key=keyboard.getKey();

                    if (dsValues[1] > dsValues[2]) {
                        //motor[0]->setVelocity(-SPEED * MAX_SPEED);
                        //motor[1]->setVelocity(SPEED * MAX_SPEED);
                        while (dsValues[2] != 0) {
                            rbmotoren[0]->setVelocity(-SPEED * MAX_SPEED);
                            rbmotoren[1]->setVelocity(SPEED * MAX_SPEED);
                            robot_->step(TIME_STEP);

                            for (int i = 0; i < 3; i++) {
                                dsValues[i] = ds[i]->getValue();
                            }
                        }
                        key = keyboard_->getKey();
                    }
                    else if (dsValues[1] < dsValues[2]) {
                        while (dsValues[1] != 0) {
                            rbmotoren[0]->setVelocity(SPEED * MAX_SPEED);
                            rbmotoren[1]->setVelocity(-SPEED * MAX_SPEED);
                            robot_->step(TIME_STEP);

                            for (int i = 0; i < 3; i++) {
                                dsValues[i] = ds[i]->getValue();
                            }
                        }
                        key = keyboard_->getKey();
                    }
                    else if (dsValues[1] == dsValues[2] && dsValues[1] != 0 && dsValues[2] != 0) {
                        // for(int i = 0; i < 2; i++){
                          // motor[i]->setVelocity(-SPEED * MAX_SPEED);
                        // }
                        // key=keyboard.getKey();
                        while (dsValues[1] != 0) {
                            rbmotoren[0]->setVelocity(SPEED * MAX_SPEED);
                            rbmotoren[1]->setVelocity(-SPEED * MAX_SPEED);
                            robot_->step(TIME_STEP);
                        }
                    }
                }
                else {
                    for (int i = 0; i < 2; i++) {
                        rbmotoren[i]->setVelocity(SPEED * MAX_SPEED);
                    }
                    key = keyboard_->getKey();
                }
            }
            //down
            else if (key == 317) {
                for (int i = 0; i < 2; i++) {
                    rbmotoren[i]->setVelocity(-SPEED * MAX_SPEED);
                }
                key = keyboard_->getKey();
            }
            //left
            else if (key == 316) {
                rbmotoren[0]->setVelocity(SPEED * MAX_SPEED);
                rbmotoren[1]->setVelocity(-SPEED * MAX_SPEED);
                key = keyboard_->getKey();
            }
            //right
            else if (key == 314) {
                rbmotoren[0]->setVelocity(-SPEED * MAX_SPEED);
                rbmotoren[1]->setVelocity(SPEED * MAX_SPEED);
                key = keyboard_->getKey();
            }


            else {
                for (int i = 0; i < 2; i++) {
                    rbmotoren[i]->setVelocity(0.0);
                }
                key = keyboard_->getKey();
            }
        }

		void WheelVelocity(double right, double left) {
			for (int i = 0; i < 10; i++) {
				if (i < 5)
					rbmotoren[i]->setVelocity(right);
				else
					rbmotoren[i]->setVelocity(left);
			}
		}
		int JoystickOperation(int axis) {
			this->joystick_->getAxisValue(axis);
		}
	};
}