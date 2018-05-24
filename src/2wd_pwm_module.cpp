#include <ros/ros.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "pca9685.h"
#include <iostream>

#define PIN_BASE 300
#define MAX_PWM 4096 // 2^12 = 4095
#define PWM_Hz 50    // 50 Hz PWM

int main(int argc, char **argv)
{
  std::cout << "PCA9685 LED example\n";

  ros::init(argc,argv,"pwm_node"); //name this node
  // when this compiled code is run, ROS will recognize it as a node called "minimal_wiringPi"

  ros::NodeHandle n; // need this to establish communications with our new node

  /*int fd = pca9685Setup(PIN_BASE, 0x40, PWM_Hz);
    if (fd < 0)
    {
      printf("Error in setup\n");
      return fd;
  }*/
}
