#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gui_pkg/serv.h"

#include <sstream>

bool exoResponse(gui_pkg::serv::Request  &req,
            gui_pkg::serv::Response &res)
{
    srand(time(nullptr));
    ROS_INFO("Service received from the node");
    ROS_INFO("with code: %s", req.code.c_str());
    ROS_INFO("Execution... ");
    sleep(5);
    float p = 0.05f;
    if(float(rand()%100)/100 > p){
        ROS_INFO("OK: Correct execution");
        res.error = "";
        return true;
    }else {
        ROS_INFO("ERROR: Failed to connect");
        res.error = "Failed to connect to the service";
        return false;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "exoskeleton_node");

    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("exo", exoResponse);
    ROS_INFO("Ready to walk");
    ros::spin();

    return 0;
}
