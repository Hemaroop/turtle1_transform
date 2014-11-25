#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc,char** argv)
{
  ros::init(argc,argv,"general_tf");
  ros::NodeHandle n;
  tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin(tf::Vector3(0.0,0.0,0.0));
  transform.setRotation(tf::Quaternion(0,0,0,1));
  ros::Rate loop_rate(10);
  while (n.ok())
    {
      br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"world","map"));
      loop_rate.sleep();
    }
  return 0;
}
