#include "connected_component.h"
#include "gui_pkg/serv.h"

ConnectedComponent::ConnectedComponent()
{
    // Trying to connect to the roscore (Master)
    nh_.reset(new ros::NodeHandle("~"));

    //Trying to connect to the server
    client_ = nh_->serviceClient<gui_pkg::serv>("/exo");
}

void ConnectedComponent::step(const std::string &code){
    gui_pkg::serv srv;
    srv.request.code = code;
    ROS_INFO("Trying to send a service call");
    if (this->client_.call(srv))
    {
      ROS_INFO("OK: Service call done");
    }
    else
    {
      ROS_ERROR("ERROR: Failed to call service server");
      throw srv.response.error;
    }
}
