#ifndef CONNECTED_COMPONENT_H
#define CONNECTED_COMPONENT_H

#include <ros/ros.h>
#include <qtimer.h>
#include <std_msgs/String.h>

class ConnectedComponent : public QObject
{
    Q_OBJECT

public:
    ConnectedComponent(int argc, char *argv[]);
    void step(const std::string &code);
    ~ConnectedComponent();

private:
    int argc;
    char **argv;
    ros::NodeHandlePtr nh_;
    ros::ServiceClient client_;


public:
    const std::string RIGHTSTEP = "12";
    const std::string LEFTSTEP = "34";
    const std::string LEFTCLOSE = "35";
    const std::string STAND = "s";
    const std::string STORAGE = "n";
    const std::string SIT = "y";

    const int CONTROL_TIME_OUT = 5000;
    std::shared_ptr<QTimer> timer_;

public slots:
    bool connect();
    bool isConnected();
    void errorMsg(std::string error);
};

#endif // CONNECTED_COMPONENT_H
