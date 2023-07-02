#include "connected_component.h"
#include "gui_pkg/Test.h"
#include <QMessageBox>
#include <QString>
#include <QCoreApplication>
#include <QTimer>
#include <QObject>

#include <iostream>
#include <regex>
#include <stdio.h>
#include <sys/wait.h>

/**
 * @brief ConnectedComponent::~ConnectedComponent
 */
ConnectedComponent::~ConnectedComponent(){
    if(stream_)
        pclose(stream_);
}

void ConnectedComponent::shutdown(){
    if(timer_->isActive())
        timer_->stop();

    nh_.reset();
    FILE * pipe;

    // Terminare rosmaster!
#ifdef _WIN32
    ROS_INFO("Sistema operativo: Windows");
    pipe = popen("tasklist | findstr rosmaster", "r");
#elif __linux__
    //ROS_INFO("Sistema operativo: Linux");
    pipe = popen("ps -e | grep -e rosmaster -e roslaunch -e serial_node.py", "r");
#elif __APPLE__
    ROS_INFO("Sistema operativo: MacOS");
    pipe = popen("ps -A | grep rosmaster", "r");
#else
    ROS_INFO("Sistema operativo sconosciuto");
    return;
#endif

    if(pipe == nullptr){
        ROS_ERROR("Failed to execute command.");
        return;
    }
    char buffer[128];
    std::string result;

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    if(pipe){
        pclose(pipe);
    }

    if(!result.empty()){
        std::string line;
        std::istringstream iss(result);

        while(std::getline(iss, line)){

            line = line.substr(line.find_first_not_of(" "), line.size());
            pid_t pid = std::stoi(line.substr(0, line.find(" ")));
            //std::cout<<"pid: " << pid;

            //ROS_INFO("killing process...");
            kill(pid, SIGKILL);
            //ROS_INFO("process killed.");

            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                int exitStatus = WEXITSTATUS(status);
                ROS_INFO("Process exited with status: %d",exitStatus);
                //std::cout << "Process exited with status: " << exitStatus;
            } else if (WIFSIGNALED(status)) {
                int signalNumber = WTERMSIG(status);
                //std::cout << "Process terminated by signal: " << signalNumber;
                ROS_INFO("Process terminated by signal:  %d", signalNumber);
            }
        }
    }
}

/**
 * @brief ConnectedComponent::initialize
 * @param argc
 * @param argv
 */
void ConnectedComponent::initialize(int argc, char **argv){
    this->argc = argc;
    this->argv = argv;
    this->timer_.reset(new QTimer());
    this->currentState_ = this->STORAGE;

    if (argc > 1 && std::string(argv[1]) == "debug") {
        debug_mode_ = true;
    }
}

/**
 * @brief ConnectedComponent::step
 * @param code
 */
bool ConnectedComponent::step(const std::string &code){
    gui_pkg::Test srv;
    srv.request.input = code;
    ROS_INFO("Trying to send a service call");
    if (this->client_.call(srv))
    {
      ROS_INFO("OK: Service call done");

      if(stoi(srv.response.output) == 1){
          ROS_ERROR("Failed to make the movement");
          return false;
      }
      else {
          ROS_INFO("Successfull movement");
          this->currentState_ = code;
          return true;
      }
    }
    else
    {
      ROS_ERROR("ERROR: Failed to call service server");
      return false;
    }
}

/**
 * @brief ConnectedComponent::connect
 * @return
 */
bool ConnectedComponent::connect(){
    bool active = this->timer_->isActive();
    if(active) this->timer_->stop();

    if(!this->isConnected() ){
        // initialize ROS
        ros::init(this->argc, this->argv, "serial_connection");

        bool isRosserialActive = false;

        if(!ros::master::check()){
            if(this->debug_mode_ == true)
                stream_ = popen("roslaunch fake_exo fake_exo.launch", "w");
            else
                stream_ = popen("roslaunch gui_pkg rosserial.launch", "w");

            if(!stream_){
                errorConnectionMsg("Error occurred during initialization.");
                return false;
            }
            isRosserialActive = true;
            sleep(6);
        }

        // Reset the NodeHandle
        nh_.reset(new ros::NodeHandle("~"));

        //Trying to connect to the server
        client_ = nh_->serviceClient<gui_pkg::Test>("/Movement_srv");

        if(!isConnected()){

            if(!isRosserialActive){
                if(debug_mode_ == true)
                    stream_ = popen("roslaunch fake_exo fake_exo.launch", "w");
                else
                    stream_ = popen("roslaunch gui_pkg rosserial.launch", "w");

                if(!stream_){
                    errorConnectionMsg("Error occurred during initialization.");
                    return false;
                }
            } else{
                errorConnectionMsg("Port failed");
            }
        }
    }

    if(active) this->timer_->start(this->CONTROL_TIME_OUT);
    return this->isConnected();
}

/**
 * @brief ConnectedComponent::isConnected
 * @return
 */
bool ConnectedComponent::isConnected(){

    if(nh_ && nh_->ok() && client_ && client_.isValid()){
        bool serviceAvailable = client_.waitForExistence(ros::Duration(.1));
        return serviceAvailable;
    }
    return false;
}

void ConnectedComponent::errorConnectionMsg(std::string error){
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
        this->shutdown();
        this->connect();
    } else if (ret == QMessageBox::Cancel) {
        // Cancel button clicked
        // Add your cancel logic here
        msgBox.close();
        this->shutdown();
    }
}

/**
 * @brief ConnectedComponent::getSerialPort
 * @return
 */
std::string ConnectedComponent::getSerialPort(){
    if(this->isConnected()){
        std::string serialPort;
        if (!nh_->getParam("port", serialPort)) {
                ROS_ERROR("Failed to retrieve 'port' parameter");
                return nullptr;
        } else return serialPort;
    }
    return nullptr;
}

/**
 * @brief ConnectedComponent::getBaudRate
 * @return
 */
int ConnectedComponent::getBaudRate(){
    if(this->isConnected()){
        int baudRate=0;

        if (!nh_->getParam("baud", baudRate)) {
                ROS_ERROR("Failed to retrieve 'baud' parameter");
                return 0;
        } else return baudRate;
    }
    return 0;
}

/**
 * @brief ConnectedComponent::getParamsList
 * @return
 */
std::vector<std::string> ConnectedComponent::getParamsList(){
    std::vector<std::string> paramsList;
    if(this->isConnected()){
        nh_->getParamNames(paramsList);
    }
    return paramsList;
}

/**
 * @brief ConnectedComponent::getParam
 * @param key
 * @return
 */
XmlRpc::XmlRpcValue ConnectedComponent::getParam(const std::string key){
    XmlRpc::XmlRpcValue param_value;
    if(this->isConnected() and nh_->hasParam(key)){
        nh_->getParam(key, param_value);
    }
    return param_value;
}

int ConnectedComponent::setParams(int baudRate, std::string serialPort){
    if(this->isConnected()){
        nh_->setParam("port", serialPort);
        nh_->setParam("baud", baudRate);
        return 1;
    }
    return 0;
}

int ConnectedComponent::setParam(std::string key, XmlRpc::XmlRpcValue value){
    if(this->isConnected()){
        nh_->setParam(key, value);
        return 1;
    }
    return 0;
}

std::string ConnectedComponent::getCurrentState(){
    return this->currentState_;
}
