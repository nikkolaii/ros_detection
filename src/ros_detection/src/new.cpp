// Created by Nikolai Persen 2021

#include "ros/ros.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_msgs/Header.h"
#include "tf/transform_broadcaster.h"
#include <iostream>
#include "std_msgs/Float32MultiArray.h"
#include "ros_detection/FloatVector.h"
// class poseTF{
//
// public:
//   int testvar;
//   poseTF(){
//   _sub = _nh.subscribe("/person_position", 1, &poseTF::callback, this);
//   _pub2 = _nh.advertise<ros_detection::FloatVector>("person_distance_vector",10000,true);
// }
//
// void callback(const geometry_msgs::Point::ConstPtr& data){
//   geometry_msgs::Point point;
//   // geometry_msgs::PoseStamped posestamped;
//   // std_msgs::Header myheader;
//   // myheader.stamp = ros::Time::now();
//   // myheader.frame_id = "person_detection_frame";
//   // path.header = myheader;
//   point.x = data -> x;
//   point.y = data -> y;
//   point.z = data -> z;
//
//
//   floatvector.point.push_back(point);
//   _pub2.publish(floatvector);
//
//
// }
//
// private:
//   ros::NodeHandle _nh;
//   ros::Subscriber _sub;
//   ros::Publisher _pub;
//   ros::Publisher _pub2;
//   tf::TransformBroadcaster _br;
//   tf::Transform _transform;
//   tf::TransformBroadcaster _br2;
//   tf::Transform _transform2;
//   tf::Quaternion quat;
//   nav_msgs::Path path;
//   ros_detection::FloatVector floatvector;
// };

class pathPublisher
{
public:

  pathPublisher(){
    pointsub = point_nh.subscribe("/person_position", 1, &pathPublisher::callback, this);
    optimized_point_pub = point_nh.advertise<geometry_msgs::Point>("Optimized_person_distance",10000,true);
  }
void callback(const ros_detection::FloatVector::ConstPtr& pointData)
{
  test.point = pointData->point;
  current_size = pointData->point.size();
  average_dist_x = 0;
  average_dist_y = 0;
  average_dist_z = 0;
  int count = 0;
  if (current_size >=25)
  {
    for (int i = current_size-25; i < current_size; i++)
    {
      average_dist_x = average_dist_x + pointData->point[i].x;
      average_dist_y = average_dist_y + pointData->point[i].y;
      average_dist_z = average_dist_z + pointData->point[i].z;
      count++;
    }
    testpoint.y = average_dist_y/count;
    testpoint.x = average_dist_x/count;
    testpoint.z = average_dist_z/count;
    optimized_point_pub.publish(testpoint);
  }
}

private:
  ros::NodeHandle point_nh;
  ros::Subscriber pointsub;
  ros::Publisher optimized_point_pub;
  ros_detection::FloatVector test;
  geometry_msgs::Point testpoint;
  int current_size;
  float average_dist_x;
  float average_dist_y;
  float average_dist_z;
  nav_msgs::Path path;


};
int main(int argc, char **argv){
  ros::init(argc, argv, "personTF");


  pathPublisher pathobj;
  ros::spin();
  return 0;
}

