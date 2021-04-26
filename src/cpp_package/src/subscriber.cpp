#include "ros/ros.h"
#include "geometry_msgs/Point.h"

#include <iostream>


void callback(const geometry_msgs::Point::ConstPtr& dataReceived){

  geometry_msgs::Point point;
  point.x = dataReceived -> x;
  point.y = dataReceived -> y;
  point.z = dataReceived -> z;
  std::cout << "x = " <<dataReceived->x << std::endl;
  std::cout << "y = " <<dataReceived->y << std::endl;
  std::cout << "z = " <<dataReceived->z << std::endl;

  ros::Rate loop_rate(10);
  loop_rate.sleep();
}
int main(int argc, char **argv){

ros::init(argc, argv, "subscribing_node");

ros::NodeHandle n;
ros::Subscriber sub = n.subscribe("topic", 10000000, callback);
ros::spin();
  return 0;
}
