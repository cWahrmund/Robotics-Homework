// This program publishes randomly-generated velocity
// messages for turtlesim.
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>  // For geometry_msgs::Twist
#include <stdlib.h> // For rand() and RAND_MAX
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/Pose.h>

turtlesim::Pose turtle_pose;

void poseData(const turtlesim::Pose& msg)
{
turtle_pose = msg;
}

int main(int argc, char **argv) {
// Initialize the ROS system and become a node.
  ros::init(argc, argv, "publish_velocity");
  ros::NodeHandle nh;

  // Create a publisher object.
  ros::ServiceClient client = nh.serviceClient<turtlesim::TeleportAbsolute>(
    "turtle1/teleport_absolute"); //links publisher to the node

  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>(
    "turtle1/cmd_vel", 1000); //links publisher to the node  

  ros::Subscriber sub = nh.subscribe("turtle1/pose", 1000,
    &poseData);  

  turtlesim::TeleportAbsolute srv;

  ros::Rate rate(2);
  srand(time(0));

  double i = 1;   
  while(ros::ok())
  {
    ros::spinOnce();
 
    geometry_msgs::Twist msg;
    msg.linear.x = double(rand())/double(RAND_MAX);
    msg.angular.z = 2*double(rand())/double(RAND_MAX) - 1;
    pub.publish(msg);

    if(turtle_pose.x < 1 || turtle_pose.x > 10 || turtle_pose.y < 1 || turtle_pose.y>10)
    {
        i = i + 1.57;        
        srv.request.x = 5.5;
        srv.request.y = 5.5;
        srv.request.theta = i;
        client.call(srv);
    }
 
    rate.sleep();
  }  


}
