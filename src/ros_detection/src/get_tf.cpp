#include "ros/ros.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PointStamped.h"
#include "std_msgs/Header.h"
#include "tf/transform_broadcaster.h"
#include <tf/transform_listener.h>
class getTF
{
public:
getTF(){
  dist_sub = nh.subscribe("/Optimized_person_distance",1, &getTF::callback, this);
  path_pub = nh.advertise<nav_msgs::Path>("person_path",100, true);
  // path_pub = nh.advertise<geometry_msgs::Point>("person_path",100, true);

}

void callback(const geometry_msgs::Point::ConstPtr& pointData)
{
  // header.stamp = ros::Time::now();
  // header.frame_id = "person_detection_frame";
  // posestamped.header = header;
  // posestamped.pose.position.x = pointData->x;
  // posestamped.pose.position.y = 0;
  // posestamped.pose.position.z = pointData->z;
  // posestamped.pose.orientation.x = 0;
  // posestamped.pose.orientation.y = 0;
  // posestamped.pose.orientation.z = 0;
  // posestamped.pose.orientation.w = 1;
  // _personPoint.header.frame_id = "person_frame";
  // _personPoint.header.stamp = posestamped.header.stamp;
  // _personPoint.point = posestamped.pose.position;
  // path.header = header;
  // path.poses.push_back(posestamped);
  // path_pub.publish(path);

  /* Creating the person_detection_frame */
  quat.setRPY(4.71238898,0,-1.57079633);
  quat.normalize();
  _transform.setOrigin(tf::Vector3(0,0,0));
  _transform.setRotation(quat);
  _br.sendTransform(tf::StampedTransform(_transform, ros::Time::now(), "zed_left_camera_frame", "person_detection_frame"));

  /* Creating the person_frame */
   _transform2.setOrigin(tf::Vector3(pointData->x, 0, pointData->z));
   _transform2.setRotation(tf::Quaternion(0,0,0,1));
   _br2.sendTransform(tf::StampedTransform(_transform2, ros::Time::now(), "person_detection_frame", "person_frame"));
  // //
  // _listener.waitForTransform("map","zed_left_camera_frame",ros::Time::now(),ros::Duration(3.0));
  // _listener.lookupTransform("map","zed_left_camera_frame",ros::Time(0), stamp);

  // point.x = stamp.getOrigin().x();
  // point.y = stamp.getOrigin().y();
  // point.z = stamp.getOrigin().z();
  // //
  // // _transform2.setOrigin(tf::Vector3(point.x, point.y, point.z));
  // // quat2.setRPY(stamp.getRotation().x(),stamp.getRotation().y(),stamp.getRotation().z());
  // // quat2.normalize();
  // // _transform2.setRotation(quat2);
  // // _br2.sendTransform(tf::StampedTransform(_transform2, ros::Time::now(), "map", "person"));
  // path_pub.publish(point);
}

private:
  ros::NodeHandle nh;
  ros::Subscriber dist_sub;
  ros::Publisher path_pub;
  tf::TransformBroadcaster _br;
  tf::Transform _transform;
  tf::TransformBroadcaster _br2;
  tf::Transform _transform2;
  tf::Quaternion quat;
  tf::Quaternion quat2;
tf::StampedTransform stamp;
  tf::TransformListener _listener;

  geometry_msgs::PoseStamped posestamped;
  geometry_msgs::Point point;
  geometry_msgs::PointStamped _personPoint;

  nav_msgs::Path path;
};
int main(int argc, char **argv)
{
  ros::init(argc,argv,"node");
  getTF tfobj;
  ros::spin();

  return 0;
}
