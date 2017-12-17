// This program publishes randomly-generated velocity
// messages for turtlesim.
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>  // For geometry_msgs::Twist
#include <std_srvs/Empty.h>
#include <stdlib.h> // For rand() and RAND_MAX

int main(int argc, char **argv) {
  // Initialize the ROS system and become a node.
  ros::init(argc, argv, "publish_velocity");
  ros::NodeHandle nh;

  // Create a publisher object.
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>(
    "turtle1/cmd_vel", 1000); //links publisher to the node

  ros::ServiceClient client = nh.serviceClient<std_srvs::Empty>(
    "/reset"); //links publisher to the node 

    std_srvs::Empty empty;
    client.call(empty);

  // Seed the random number generator.
  srand(time(0));

  // Loop at 2Hz until the node is shut down.
  double i = .1;
  ros::Rate rate(2);
  while(ros::ok()) {
    // Create and fill in the message.  The other four
    // fields, which are ignored by turtlesim, default to 0.
    geometry_msgs::Twist msg; //Object msgs
    msg.linear.x = i;
    msg.angular.z = 1.1;

    // Publish the message.
    pub.publish(msg);

    // Send a message to rosout with the details.
    ROS_INFO_STREAM("Sending random velocity command:"
      << " linear=" << msg.linear.x
      << " angular=" << msg.angular.z);

    // Wait until it's time for another iteration.
    rate.sleep();
    i = i + .1;

    if(i >= 6)
    {
        return 0;
    }

  }
}
