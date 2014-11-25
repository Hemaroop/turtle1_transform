#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc,char** argv)
{
  ros::init(argc,argv,"base_to_cam");
  ros::NodeHandle n;
  tf::Transform transform;
  tf::TransformBroadcaster broadcaster;
  ros::Rate loop_rate(10);
  while (n.ok())
    {
      tf::Quaternion tf_quat=tf::createQuaternionFromRPY(0.0f,0.0f,3.1417f);
      transform.setRotation(tf_quat);
      transform.setOrigin(tf::Vector3(-0.13,0.0,0.25));
      broadcaster.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"base_link","camera_link"));
      loop_rate.sleep();
    }
  return 0;
}
