#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

double vx=0.0f;
double vy=0.0f;
double vth=0.0f;
double x=0.0f;
double y=0.0f,z=0.0f;
double yaw=0.0f,roll=0.0f,pitch=0.0f;

void TwistCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  vx=(-1*msg->linear.x);
  //vy=msg->linear.y;
  vth=msg->angular.z;
}

int main(int argc,char** argv)
{
  ros::init(argc,argv,"odom_to_base");
  ros::NodeHandle n;
  tf::Transform transform;
  ros::Subscriber sub=n.subscribe("cmd_vel",1,TwistCallback);
  ros::Publisher odom_pub=n.advertise<nav_msgs::Odometry>("odom",10);
  tf::TransformBroadcaster odom_2_base;
  ros::Time current_time=ros::Time::now();
  ros::Rate loop_rate(10);
  ros::Time last_time=ros::Time::now();
  while(n.ok())
    {
      ros::spinOnce();
      current_time=ros::Time::now();
      double dt=(current_time-last_time).toSec();
      x+=(vx*cos(yaw)-vy*sin(yaw))*dt;
      y+=(vy*cos(yaw)+vx*sin(yaw))*dt;
      yaw+=vth*dt;
      tf::Quaternion quat_ob=tf::createQuaternionFromRPY(roll,pitch,yaw);
      transform.setRotation(quat_ob);
      transform.setOrigin(tf::Vector3(x,y,z));
      odom_2_base.sendTransform(tf::StampedTransform(transform,current_time,"odom","base_link"));
      nav_msgs::Odometry odom;
      odom.header.stamp = current_time;
      odom.header.frame_id = "odom";
      odom.pose.pose.position.x = x;
      odom.pose.pose.position.y = y;
      odom.pose.pose.position.z = 0.0;
      odom.pose.pose.orientation =tf::createQuaternionMsgFromYaw(yaw);
      odom.child_frame_id = "base_link";
      odom.twist.twist.linear.x = vx;
      odom.twist.twist.linear.y = vy;
      odom.twist.twist.angular.z = vth;
      odom_pub.publish(odom);
      last_time=current_time;
      loop_rate.sleep();
    }
  return 0;
}
