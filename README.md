# <img src="https://github.com/cristianbass01/GUI_robotic_exoskeleton/assets/72708597/bb79ef7b-30f0-4e3a-9ffb-870d1a9cd80b" alt="Logo" width="50" height="50"> A GUI for Assistive Walking Exoskeleton
## 1. Introduction
This is an intuitive and effective Graphical User Interface for controlling an assistive walking exoskeleton for reabilitation. 

The interface is implemented in C++ with the aid of the Qt libraries for the graphics part and the connection to ROS. The main objective of the work was to develop a user-friendly interface so that the physiotherapist can focus on the patient and the effectiveness of the treatment. 

The validation of the interface was conducted through tests on a prototype exoskeleton, demonstrating its effectiveness and ease of use. 

## 2. Installation on Ubuntu
### 2.1 Download files
Open the terminal and clone the repo:
```
git clone https://github.com/cristianbass01/GUI_robotic_exoskeleton.git
```
or download the zip file and then decompress it:

```
wget https://github.com/cristianbass01/GUI_robotic_exoskeleton/archive/refs/heads/main.zip
unzip main.zip -d ./GUI_robotic_exoskeleton
```
Go to the repo directory created:
```
cd GUI_robotic_exoskeleton 
```

### 2.2 Setup environment
In order to be able to run this application, you need to have ROS Noetic installed on your system.
If not, you can install it using:
```
wget -c https://raw.githubusercontent.com/qboticslabs/ros_install_noetic/master/ros_install_noetic.sh && chmod +x ./ros_install_noetic.sh && ./ros_install_noetic.sh
```
If you have problems installing it, please refer to the official [ROS Noetic website](http://wiki.ros.org/noetic/Installation) for instructions.

After the installation of ROS noetic, you could make the setup.sh file executable and run it:
```
chmod +x setup.sh
./setup.sh
```
### 2.3 Launch file  
A new launch.sh file is being created, run it:
```
./launch.sh
```
### 2.4 Debug Mode
It is possible to run the application in debug mode without the connection to the exoskeleton (just to test how it works):
```
./launch.sh debug
```


## 3. Authors
- Cristian Bassotto
- Nicola Busato
