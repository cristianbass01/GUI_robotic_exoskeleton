#include "connected_component.h"
#include "gui_pkg/serv.h"
#include <QMessageBox>
#include <QString>
#include <QCoreApplication>
#include <QTimer>
#include <QObject>

ConnectedComponent::ConnectedComponent(int argc, char *argv[])
{
    this->argc = argc;
    this->argv = argv;
    this->timer_.reset(new QTimer());
}

ConnectedComponent::~ConnectedComponent(){
    delete argv;
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

bool ConnectedComponent::connect(){
    bool active = this->timer_->isActive();
    if(active) this->timer_->stop();

    if(!this->isConnected() ){
        // launch rosserial and master using command line
        // std::system("roslaunch rosserial_python rosserial.launch");
        //std::system("gnome-terminal --command='rosrun fake_exo exoskeleton_node'");
        FILE * pipe = popen("rosrun fake_exo exoskeleton_node", "r");
        if(!pipe)
            return this->connect();

        // initialize ROS
        ros::init(this->argc, this->argv, "gui_connection");

        if(ros::master::check()){
            // Reset the NodeHandle
            nh_.reset(new ros::NodeHandle("~"));

            //Trying to connect to the server
            client_ = nh_->serviceClient<gui_pkg::serv>("/exo");

            if(!isConnected()){
                errorMsg("Error occurred during\nconnection to the device.");
            }
        }
        else {
            errorMsg("Error occurred during\nconnection to the master");
        }
    }

    if(active) this->timer_->start(this->CONTROL_TIME_OUT);
    return this->isConnected();
}

bool ConnectedComponent::isConnected(){

    if(nh_ && nh_->ok() && client_ && client_.isValid()){
        bool serviceAvailable = client_.waitForExistence(ros::Duration(.1));
        return serviceAvailable;
    }
    return false;
}

void ConnectedComponent::errorMsg(std::string error){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Error");
    msgBox.setText(QString::fromStdString(error));
    msgBox.setInformativeText("Do you want to retry?");
    msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Retry);

    int ret = msgBox.exec();

    if (ret == QMessageBox::Retry) {
        // Retry button clicked
        // Add your retry logic here
        msgBox.close();
        this->connect();
    } else if (ret == QMessageBox::Cancel) {
        // Cancel button clicked
        // Add your cancel logic here
        msgBox.close();
    }
}
