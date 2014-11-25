#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc,char** argv)
{
  ros::init(argc,argv,"map_to_odom");
  ros::NodeHandle n;
  double yaw=0.0f;
  tf::TransformBroadcaster mo_broadcaster;
  ros::Rate loop_rate(10);
  while (n.ok())
    {
      tf::Quaternion mto_quat=tf::createQuaternionFromRPY(0.0f,0.0f,yaw);
      tf::Transform transform;
      transform.setOrigin(tf::Vector3(0.2,0.2,0.0));
      transform.setRotation(mto_quat);
      mo_broadcaster.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"map","odom"));
      loop_rate.sleep();
    }
  return 0;
}
