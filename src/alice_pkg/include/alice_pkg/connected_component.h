#ifndef CONNECTED_COMPONENT_H
#define CONNECTED_COMPONENT_H

#include <ros/ros.h>
#include <qtimer.h>
#include <std_msgs/String.h>
#include <QTimer>
#include <QSharedPointer>

#include <XmlRpc.h>

class ConnectedComponent
{

public:
    /**
     * @brief Singleton pattern method getInstance
     * @return a reference to the 'instance' variable
     */
    static ConnectedComponent& getInstance(){
        // Declare a static variable named 'instance' of type ConnectedComponent
        // This variable will hold the single instance of the class
        static ConnectedComponent instance;
        return instance;
    }

    /**
     * @brief initialize the connected class (initialize argc, argv, reset the timer,
     *        put the currentState in storage and set the debug mode)
     * @param argc : number of parameters passed to main
     * @param argv : vector of parameters passed to main
     */
    void initialize(int argc, char *argv[]);

    /**
     * @brief Call the service of the exo to do a movement and update currentState
     * @param code of the movement
     * @return if the movement was successful return true, otherwise false
     */
    bool step(const std::string &code);

    /**
     * @brief destroy the object and close the stream_
     */
    ~ConnectedComponent();

private:
    /**
     * @brief argc : number of parameters passed to main
     */
    int argc;

    /**
     * @brief argv : vector of parameters passed to main
     */
    char **argv;

    /**
     * @brief nh_ pointer of class NodeHandlerPtr that refer
     * to our node /serial_connection
     */
    ros::NodeHandlePtr nh_;

    /**
     * @brief client_ client that allow to send and receive services
     */
    ros::ServiceClient client_;

    /**
     * @brief stream_ : file stream to process roslaunch
     */
    FILE * stream_;

    /**
     * @brief current state of the connected component (ex. Exoskeleton)
     */
    std::string currentState_;

    /**
     * @brief debug_mode : if true connect to fake_exo_pkg, otherwise to rosserial
     */
    bool debug_mode_ = false;

    /**
     * @brief ConnectedComponent : private constructor (Singleton)
     */
    ConnectedComponent(){}
    // no copy

    /**
     * @brief ConnectedComponent : delete copy
     */
    ConnectedComponent(const ConnectedComponent&) = delete;

    /**
     * @brief operator = : delete copy
     */
    void operator= (const ConnectedComponent&) = delete;

public:
    /**
     * @brief RIGHTSTEP : code to move the right foot
     */
    const std::string RIGHTSTEP = "12";

    /**
     * @brief LEFTSTEP : code to move the left foot
     */
    const std::string LEFTSTEP = "34";

    /**
     * @brief LEFTCLOSE : code to close the feet (moving left foot)
     */
    const std::string LEFTCLOSE = "35";

    /**
     * @brief STAND : code to stand position
     */
    const std::string STAND = "s";

    /**
     * @brief STORAGE : : code to storage position
     */
    const std::string STORAGE = "n";

    /**
     * @brief SIT : code to sit position
     */
    const std::string SIT = "y";

    /**
     * @brief CONTROL_TIME_OUT : time that pass from an automatic check
     * of connection and the one after (if not shutdown)
     */
    const int CONTROL_TIME_OUT = 5000;

    /**
     * @brief timer_ : timer to check of connection loop
     */
    std::shared_ptr<QTimer> timer_;

    /**
     * @brief If connected, ask ros parameter "port"
     * @return the port that rosserial use to connect to the device
     */
    std::string getSerialPort();

    /**
     * @brief If connected, ask ros parameter "baud"
     * @return the baud rate that rosserial use to connect to the device
     */
    int getBaudRate();

    /**
     * @brief if connected, ask the names of all ros parameters.
     * @return vector of strings with names of ros parameters
     */
    std::vector<std::string> getParamsList();

    /**
     * @brief if connected, aske the value of a specific ros parameter
     * @param name of the ros parameter
     * @return XmlRcpValue with the ros parameter value
     */
    XmlRpc::XmlRpcValue getParam(const std::string key);

    /**
     * @brief if connected, change/set the ros parameter "baud" rate and "port"
     * @param baudRate : value of baud rate to set
     * @param serialPort : value of the port to set
     * @return true if connected, false otherwise
     */
    int setParams(int baudRate, std::string serialPort);

    /**
     * @brief if connected, change/set the specific ros parameter passed
     * @param key : name of ros parameter to change or set
     * @param value : new value of the ros parameter
     * @return true if connected, false otherwise
     */
    int setParam(std::string key, XmlRpc::XmlRpcValue value);

    /**
     * @brief get the device current state (movement code)
     * @return a string with the device current state (movement code)
     */
    std::string getCurrentState();

    /**
     * @brief Shutdown the connection with the device, shutting down ros.
     * -> stop the timer.
     * -> Search for the pid of rosmaster, roslaunch and serial_node.py
     *    and kill them.
     */
    void shutdown();

public slots:
    /**
     * @brief Try to connect to the device:
     *   -> pause the timer
     *   -> initialize ros
     *   -> launch roslaunch
     *   -> subscribe to Movement_srv
     *   -> check connected
     *   -> restart timer
     * @return true if connected, false otherwise
     */
    bool connect();

    /**
     * @brief check the connection: nh_, nh_->ok(), client_, client_isValid()
     *    client_.waitForExistence
     * @return true if connected, false otherwise
     */
    bool isConnected();

    /**
     * @brief execute a QMessageBox with Reply and Cancel button.
     *   Retry is used to retry to connect
     * @param error
     */
    void errorConnectionMsg(std::string error);
};

#endif // CONNECTED_COMPONENT_H
