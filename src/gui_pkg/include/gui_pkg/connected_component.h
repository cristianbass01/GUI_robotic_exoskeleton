#ifndef CONNECTED_COMPONENT_H
#define CONNECTED_COMPONENT_H

#include <ros/ros.h>
#include <qtimer.h>
#include <std_msgs/String.h>

class ConnectedComponent
{
public:
    ConnectedComponent(int argc, char *argv[]);
    void step(const std::string &code);

private:
    int argc;
    char **argv;
    ros::NodeHandlePtr nh_;
    ros::ServiceClient client_;

public:
    const std::string LEFTSTEP = "12";
    const std::string RIGHTSTEP = "34";
    const std::string PAIR = "51";

    void connect();
    bool isConnected();
    void errorMsg(std::string error);
};

#endif // CONNECTED_COMPONENT_H
