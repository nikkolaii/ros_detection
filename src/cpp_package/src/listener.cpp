#include "ros/ros.h"
#include "geometry_msgs/Point.h"

int main(int argc, char **argv){

  ros::init(argc, argv, "noded");

  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::Point>("topic",1000);

  geometry_msgs::Point number;
  while (ros::ok()) {
    number.x = 1.23492342389472389;
    number.y = 2;
    number.z = 3.23492342389472389;
    pub.publish(number);
  }


  return 0;
}
