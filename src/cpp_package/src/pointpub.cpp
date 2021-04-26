#include "ros/ros.h"
#include "geometry_msgs/Point.h"

int main(int argc, char **argv){
ros::init(argc,argv, "nodenode");
ros::NodeHandle nh;
ros::Publisher pub = nh.advertise<geometry_msgs::Point>("point_topic",1000);
geometry_msgs::Point point;
point.x = 1;
point.y = 2;
point.z = 3;
while (ros::ok()) {
  pub.publish(point);
  /* code */
}
  return 0;
}
