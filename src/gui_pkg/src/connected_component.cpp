#include "connected_component.h"
#include "gui_pkg/serv.h"
#include <QMessageBox>
#include <QString>
#include <QCoreApplication>
#include <QTimer>
#include <QObject>

#include <iostream>
#include <regex>
#include <stdio.h>
#include <sys/wait.h>

ConnectedComponent::ConnectedComponent(int argc, char *argv[])
{
    this->argc = argc;
    this->argv = argv;
    this->timer_.reset(new QTimer());
}

ConnectedComponent::~ConnectedComponent(){
    nh_.reset();

    FILE * pipe = popen("ps -e | grep rosmaster", "r");
    if(pipe == nullptr){
        ROS_ERROR("Failed to execute command.");
        return;
    }
    char buffer[128];
    std::string result;

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    if(pipe)
        pclose(pipe);

    if(!result.empty()){
        result = result.substr(result.find_first_not_of(" "), result.size());
        pid_t pid = std::stoi(result.substr(0, result.find(" ")));
        ROS_INFO("pid: %d",pid);

        ROS_INFO("killing process...");
        kill(pid, SIGKILL);
        ROS_INFO("process killed.");

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exitStatus = WEXITSTATUS(status);
            ROS_INFO("Process exited with status: %d",exitStatus);
        } else if (WIFSIGNALED(status)) {
            int signalNumber = WTERMSIG(status);
            ROS_INFO("Process terminated by signal:  %d", signalNumber);
        }

    }
    if(stream_)
        pclose(stream_);
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
        // initialize ROS
        ros::init(this->argc, this->argv, "gui_connection");


        if(! (ros::master::check())){

            // Simulation
            stream_ = popen("roslaunch fake_exo fake_exo.launch", "w");

            // Actual rosserial node
            //stream_ = popen("roslaunch rosserial_python rosserial.launch", "w");
            if(!stream_){
                errorMsg("Error occurred during\nconnection to the device.");
                return false;
            }
            sleep(2);
        }

        // Reset the NodeHandle
        nh_.reset(new ros::NodeHandle("~"));

        //Trying to connect to the server
        client_ = nh_->serviceClient<gui_pkg::serv>("/exo");

        if(!isConnected()){
            errorMsg("Error occurred during\nconnection to the device.");
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
