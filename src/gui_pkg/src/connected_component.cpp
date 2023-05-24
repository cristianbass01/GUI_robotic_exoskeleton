#include "connected_component.h"
#include "gui_pkg/serv.h"
#include <QMessageBox>
#include <QString>

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

    try {
        ros::init(this->argc, this->argv, "gui_connection");
    } catch (std::exception& e) {
        std::string error = "Failed to initialize ROS: " + std::string(e.what());
        ROS_ERROR_STREAM(error);
        errorMsg(error);
    }

    try{
        // Reset the NodeHandle
        nh_.reset(new ros::NodeHandle("~"));
    }
    catch (const std::exception& e){
        std::string error = "Failed to reset NodeHandle: " + std::string(e.what());
        ROS_ERROR_STREAM(error);
        errorMsg(error);
    }


    try{
        //Trying to connect to the server
        client_ = nh_->serviceClient<gui_pkg::serv>("/exo");
    }
    catch (const std::exception& e)
    {
        std::string error = "Exception occurred during service call: " + std::string(e.what());
        ROS_ERROR_STREAM(error);
        errorMsg(error);
    }
}

bool ConnectedComponent::isConnected(){

    if(nh_ && nh_->ok() && client_ && client_.isPersistent() && client_.isValid()){
        return true;
    }
    return false;
}

void ConnectedComponent::errorMsg(std::string error){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Error");
    msgBox.setText(QString::fromStdString(error));
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
