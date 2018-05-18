/*
 *  ONE_A_GPIO : GPIO 5 (Pin 29)
 *  ONE_B_GPIO : GPIO 6 (Pin 31)
 *  TWO_A_GPIO : GPIO 19 (Pin 35)
 *  TWO_B_GPIO : GPIO 26 (Pin 37)w
*/

#include<ros/ros.h>   // Include ROS Library
#include <wiringPi.h> // Include wiringPi Library
#include <iostream>
#include <unistd.h>

#define ONE_A_GPIO 5
#define ONE_B_GPIO 6
#define TWO_A_GPIO 19
#define TWO_B_GPIO 26

#define OFF 0
#define ON 1

using namespace std;

void forward(unsigned int microseconds)
{
  // Left Wheel
  digitalWrite(ONE_A_GPIO , ON);
  digitalWrite(ONE_B_GPIO , OFF);
  // Right Wheel
  digitalWrite(TWO_A_GPIO , ON);
  digitalWrite(TWO_B_GPIO , OFF);

  usleep(microseconds * 1000);

  // Left Wheel
  digitalWrite(ONE_A_GPIO , OFF);
  // Right Wheel
  digitalWrite(TWO_A_GPIO , OFF);

}

int main(int argc, char **argv)
{
  unsigned int mSec;
  cout << "Motor Node\n";

  ros::init(argc,argv,"motor_node"); //name this node
  // when this compiled code is run, ROS will recognize it as a node called "minimal_wiringPi"

  ros::NodeHandle n; // need this to establish communications with our new node


  wiringPiSetupGpio(); // Initalize Pi

  pinMode(ONE_A_GPIO, OUTPUT);
  pinMode(ONE_B_GPIO, OUTPUT);
  pinMode(TWO_A_GPIO, OUTPUT);
  pinMode(TWO_B_GPIO, OUTPUT);

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




