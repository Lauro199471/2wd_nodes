/**********************************************************************;
* Project           : Two Wheel Robot
*
* Program name      : 2wd_motor.cpp
*
* Author            : Lauro Cabral
*
* Date created      : May 24 , 2018
*
* Purpose           : Motor Motion code for a simple ROS project
*
* Revision History  : 0.1
*
* Notes             :
*                     Ideal Motor Freq: 5-20 KHz
*
*                     Left Wheel A  : PWM 0
*                     Left Wheel B  : PWM 1
*                     Right Wheel A : PWM 2
*                     Right Wheel A : PWM 3
**********************************************************************/

#include<ros/ros.h>   // Include ROS Library
#include <wiringPi.h> // Include wiringPi Library
#include <iostream>
#include <unistd.h>
#include "pca9685.h"

#define ONE_A_GPIO 5
#define ONE_B_GPIO 6
#define TWO_A_GPIO 19
#define TWO_B_GPIO 26

#define OFF 0
#define ON 1

#define PIN_BASE 100

#define MAX_PWM 4095 // 12-bit Pwm
#define MIN_PWM 0

#define NUM_PINS 16  // PCA9685 has 16 pwm pins
#define HERTZ 10000  // 10Khz

#define PWM_0 0
#define PWM_1 1
#define PWM_2 2
#define PWM_3 3
#define PWM_4 4
#define PWM_5 5
#define PWM_6 6
#define PWM_7 7
#define PWM_8 8
#define PWM_9 9
#define PWM_10 10
#define PWM_11 11
#define PWM_12 12
#define PWM_13 13
#define PWM_14 14
#define PWM_15 15
#define PWM_ALL 16

using namespace std;

// ===================================
//        Motor Motion Functions
// ===================================
void forward(unsigned int microseconds)
{
  // Left Wheel
  pwmWrite(PIN_BASE + PWM_0 , MAX_PWM);
  pwmWrite(PIN_BASE + PWM_1 , MIN_PWM);

  // Right Wheel
  pwmWrite(PIN_BASE + PWM_2 , MAX_PWM);
  pwmWrite(PIN_BASE + PWM_3 , MIN_PWM);

  usleep(microseconds * 1000);

  // OFF
  pwmWrite(PIN_BASE + PWM_ALL, MIN_PWM);
}

void backward(unsigned int microseconds)
{
  // Left Wheel
  pwmWrite(PIN_BASE + PWM_0 , MIN_PWM);
  pwmWrite(PIN_BASE + PWM_1 , MAX_PWM);

  // Right Wheel
  pwmWrite(PIN_BASE + PWM_2 , MIN_PWM);
  pwmWrite(PIN_BASE + PWM_3 , MAX_INPUT);

  usleep(microseconds * 1000);

  // OFF
  pwmWrite(PIN_BASE + PWM_ALL, MIN_PWM);
}

// ===================================
//           Main Functions
// ===================================
int main(int argc, char **argv)
{
  unsigned int mSec;
  cout << "Motor Node\n";

  ros::init(argc,argv,"motor_node"); //name this node
  // when this compiled code is run, ROS will recognize it as a node called "minimal_wiringPi"

  ros::NodeHandle n; // need this to establish communications with our new node
  int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);

  if (fd < 0)
  {
    printf("Error in setup\n");
    return fd;
  }

  pca9685PWMReset(fd);

  ros::Rate r(1000); // 1 khz for spin (Industry Standard)

  while(ros::ok())
  {

    cout << "Enter Mirco-seconds: ";
    cin >> mSec;
    forward(mSec);
    cout << "\tForward DONE\n";
    backwards(mSec);
    cout << "\tBackwards DONW\n";
    ros::spinOnce();
    r.sleep();

  }

  // OFF
  pwmWrite(PIN_BASE + PWM_ALL, MIN_PWM);

  return 0;
}




