#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "tf/transform_broadcaster.h"
#include "nav_msgs/Odometry.h"
class subpub
{
public:
  subpub(){
    _pub = _n.advertise<geometry_msgs::Point>("pub_by_class",100);
    _sub = _n.subscribe("/RosAria/pose", 1, &subpub::callbackFunction, this);
  }
void callbackFunction(const nav_msgs::Odometry::ConstPtr& msg){
  geometry_msgs::Point point;
  point.x = msg-> pose.pose.position.x;
  point.y = msg-> pose.pose.position.y;
  point.z = msg-> pose.pose.position.z;
  _pub.publish(point);
  _transform.setOrigin(tf::Vector3(msg -> pose.pose.position.x, msg -> pose.pose.position.y, msg -> pose.pose.position.z));
  _transform.setRotation(tf::Quaternion(0,0,0,1));
  _br.sendTransform(tf::StampedTransform(_transform, ros::Time::now(), "odom", "Tord_tror_han_kan"));
}

private: //attributes
  ros::NodeHandle _n;
  ros::Subscriber _sub;
  ros::Publisher _pub;
  tf::TransformBroadcaster _br;
  tf::Transform _transform;

};

int main(int argc, char **argv){

ros::init(argc, argv, "tf_broadcaster");
subpub myobject;
ros::spin();


  return 0;
}
