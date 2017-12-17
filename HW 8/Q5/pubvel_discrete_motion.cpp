// This program publishes randomly-generated velocity
// messages for turtlesim.
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>  // For geometry_msgs::Twist
#include <stdlib.h> // For rand() and RAND_MAX
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/Pose.h>
#include <std_srvs/Empty.h>

bool moveLinear(std_srvs::Empty::Request  &req,
  std_srvs::Empty::Response &res)
{
  return true;
}

bool moveAngular(std_srvs::Empty::Request  &req,
  std_srvs::Empty::Response &res)
{
  return true;
}                

int main(int argc, char **argv) {
// Initialize the ROS system and become a node.
  ros::init(argc, argv, "publish_velocity");
  ros::NodeHandle nh;

  ros::ServiceServer move_linear_service = nh.advertiseService("move_linear", moveLinear);
  ros::ServiceServer move_angular_service = nh.advertiseService("move_angular", moveAngular);

  // Create a publisher object.
  ros::ServiceClient client = nh.serviceClient<turtlesim::TeleportAbsolute>(
    "turtle1/teleport_absolute"); //links publisher to the node

  turtlesim::TeleportAbsolute srv;

  srv.request.x = 5.45;
  srv.request.y = 5.45;
  srv.request.theta = 0;
  client.call(srv);

  srv.request.x = 2.45;
  srv.request.y = 5.45;
  srv.request.theta = 0;
  client.call(srv);

  srv.request.x = 2.45;
  srv.request.y = 3.45;
  srv.request.theta = 0;
  client.call(srv);

  srv.request.x = 5.45;
  srv.request.y = 3.45;
  srv.request.theta = 0;
  client.call(srv);

  srv.request.x = 5.45;
  srv.request.y = 5.45;
  srv.request.theta = 0;
  client.call(srv);
}

