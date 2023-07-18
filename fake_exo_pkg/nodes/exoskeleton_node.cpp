#include "ros/ros.h"
#include "std_msgs/String.h"
#include "fake_exo_pkg/Test.h"

#include <sstream>

bool exoResponse(fake_exo_pkg::Test::Request  &req,
            fake_exo_pkg::Test::Response &res)
{
    srand(time(nullptr));
    ROS_INFO("Service received from the node");
    ROS_INFO("with code: %s", req.input.c_str());
    ROS_INFO("Execution... ");
    sleep(2);
    float p = 0;
    if(float(rand()%100)/100 >= p){
        ROS_INFO("OK: Correct execution");
        res.output = "0";
        return true;
    }else {
        ROS_INFO("ERROR: Failed to connect");
        res.output = "1";
        return true;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "exoskeleton_node");

    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("Movement_srv", exoResponse);
    ROS_INFO("Ready to walk");
    ros::spin();

    return 0;
}
