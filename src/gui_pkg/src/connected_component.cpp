#include "connected_component.h"
#include "gui_pkg/serv.h"

ConnectedComponent::ConnectedComponent(int argc, char *argv[])
{
    this->argc = argc;
    this->argv = argv;
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

void ConnectedComponent::connect(){

    ros::init(this->argc, this->argv, "gui_connection");

    // Trying to connect to the roscore (Master)
    nh_.reset(new ros::NodeHandle("~"));

    //Trying to connect to the server
    client_ = nh_->serviceClient<gui_pkg::serv>("/exo");
}

bool ConnectedComponent::isConnected(){

    if(nh_ && nh_->ok() && client_ && client_.isPersistent() && client_.isValid()){
        return true;
    }
    return false;
}
