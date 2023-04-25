#include <ros/ros.h>
#include <std_msgs/Int64.h>
#include <cstdlib>
#include <iostream>

int main (int argc, char **argv)
{
srand((unsigned) time(NULL));    
ros::init(argc, argv, ("number_publisher_cpp"), ros::init_options::AnonymousName);
ros::NodeHandle nh;
ros::Publisher pub = nh.advertise<std_msgs::Int64>("/number",10);
ros::Rate rate(1);
int random = (rand() % 101);
while (ros::ok()) {
std_msgs::Int64 msg;
msg.data = random;
int myInt = msg.data;
ROS_INFO("%d",myInt);
pub.publish(msg);
rate.sleep();
}
}