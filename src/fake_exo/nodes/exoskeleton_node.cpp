#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gui_pkg/serv.h"

#include <sstream>

bool walk(gui_pkg::serv::Request  &req,
            gui_pkg::serv::Response &res)
{
  ROS_INFO("Servizio ricevuto");
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "exoskeleton_node");

  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("walking", walk);
  ROS_INFO("Ready to walk");
  ros::spin();

  return 0;
}
