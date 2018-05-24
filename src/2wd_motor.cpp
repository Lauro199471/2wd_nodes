/*
 *  Ideal Freq: 5-20 KHz
 *  ONE_A_GPIO : GPIO 5 (Pin 29)
 *  ONE_B_GPIO : GPIO 6 (Pin 31)
 *  TWO_A_GPIO : GPIO 19 (Pin 35)
 *  TWO_B_GPIO : GPIO 26 (Pin 37)w
*/

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

using namespace std;

void forward(unsigned int microseconds)
{
  // Left Wheel
  pwmWrite(PIN_BASE | PWM_0 | PWM_3 , MAX_PWM);

  usleep(microseconds * 1000);

  // OFF
   pwmWrite(PIN_BASE + 16, 0);
}

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
    cout << "\tDONE\n";
    ros::spinOnce();
    r.sleep();

  }

  // Left Wheel
  digitalWrite(ONE_A_GPIO , OFF);
  digitalWrite(ONE_B_GPIO , OFF);
  // Right Wheel
  digitalWrite(TWO_A_GPIO , OFF);
  digitalWrite(TWO_B_GPIO , OFF);

  return 0;
}




