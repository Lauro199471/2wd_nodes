cmake_minimum_required(VERSION 2.8.3)
project(2wd_nodes)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  roscpp
  std_msgs
)

find_package(Boost REQUIRED COMPONENTS system)
FIND_LIBRARY(WIRINGPI_LIBRARY wiringPi /opt/wiringPi)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES seven_dof_arm_test
#  CATKIN_DEPENDS cmake_modules interactive_markers moveit_core moveit_ros_perception moveit_ros_planning_interface pluginlib roscpp std_msgs
#  DEPENDS system_lib
  CATKIN_DEPENDS message_runtime
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(${catkin_INCLUDE_DIRS} ${WIRINGPI_LIBRARY})

## Declare a cpp executable
add_executable(2wd_motor src/2wd_motor.cpp)

## Add cmake target dependencies of the executable/library
add_dependencies(2wd_motor 2wd_nodes_generate_messages_cpp wiringPi)


## Specify libraries to link a library or executable target against
target_link_libraries(2wd_motor  ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY})




