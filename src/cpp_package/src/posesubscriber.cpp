#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Point.h"

#include <iostream>
//void mypublisher(const geometry_msgs::Point::ConstPtr& point){

//}
geometry_msgs::Point point;
void callback(const nav_msgs::Odometry::ConstPtr& posedata){

point = posedata -> pose.pose.position;

}

int main(int argc, char **argv){

ros::init(argc, argv, "posendoe");
ros::NodeHandle n;
ros::Subscriber subs = n.subscribe("RosAria/pose", 10000, callback);
std::cout<<posedata -> pose.pose.position<<std::endl;
ros::spin();
  return 0;
}
