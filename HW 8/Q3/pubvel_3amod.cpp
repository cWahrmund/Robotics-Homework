#include <ros/ros.h>
#include <geometry_msgs/Twist.h>  // For geometry_msgs::Twist
#include <turtlesim/TeleportAbsolute.h>
#include <stdlib.h> // For rand() and RAND_MAX


int main(int argc, char **argv) {
  // Initialize the ROS system and become a node.
  ros::init(argc, argv, "publish_velocity");
  ros::NodeHandle nh;

  // Create a publisher object.
  ros::ServiceClient client = nh.serviceClient<turtlesim::TeleportAbsolute>(
    "turtle1/teleport_absolute"); //links publisher to the node

  turtlesim::TeleportAbsolute srv;

  srv.request.x = 5.5;
  srv.request.y = 1.5;
  srv.request.theta = 0.0;
  client.call(srv);

  srv.request.x = 7.5;
  srv.request.y = 1.5;
  srv.request.theta = 0.0;
  client.call(srv);

  return 0;
}
