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
    //delete argv;
    std::cout << "Distruttore";
    nh_.reset();
    ros::shutdown();
/*
    if(stream_ && pid_.size()>0){
        int status;
        for(pid_t pid : pid_){
            if (waitpid(pid, &status, WNOHANG) == 0) {
                //Termina manualmente il processo utilizzando SIGTERM
                kill(pid, SIGTERM);

                // Attendere la terminazione effettiva del processo
                waitpid(pid, &status, 0);
            }

            if (WIFEXITED(status)) {
                int exitStatus = WEXITSTATUS(status);
                std::cout << "Process exited with status: " << exitStatus << std::endl;
            } else if (WIFSIGNALED(status)) {
                int signalNumber = WTERMSIG(status);
                std::cout << "Process terminated by signal: " << signalNumber << std::endl;
            }
        }
    pclose(stream_);
    }*/

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
        // std::system("gnome-terminal --command='rosrun fake_exo exoskeleton_node'");

        // initialize ROS
        ros::init(this->argc, this->argv, "gui_connection");

        /*
        if(! (ros::master::check())){
            //std::system("gnome-terminal --command='roscore'");
            stream_ = popen("roslaunch fake_exo fake_exo.launch", "r");
            if(!stream_){
                errorMsg("Error occurred during\nconnection to the device.");
                return false;
            }

            pid_.append(fileno(stream_));

            // Leggi tutte le righe e recupera i valori di "pid [valore]"
            char buffer[256];
            std::string output;
            while (fgets(buffer, sizeof(buffer), stream_)) {
                output += buffer;  // Accumula l'output completo
            }

            // Crea un'espressione regolare per trovare i valori di "pid [valore]"
            std::regex regex("pid\\s+\\[([0-9]+)\\]");

            // Crea un oggetto std::smatch per memorizzare le corrispondenze
            std::smatch match;

            // Trova e stampa tutti i valori di "pid [valore]"
            std::string::const_iterator searchStart(output.cbegin());
            while (std::regex_search(searchStart, output.cend(), match, regex)) {
                std::cout << "PID: " << match[1] << std::endl;
                pid_.append(stoi(match[1]));
                searchStart = match.suffix().first;  // Continua la ricerca dalla fine dell'ultima corrispondenza
            }
        }
        */

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
