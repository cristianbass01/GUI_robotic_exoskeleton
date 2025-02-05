# <img src="https://github.com/cristianbass01/GUI_robotic_exoskeleton/assets/72708597/bb79ef7b-30f0-4e3a-9ffb-870d1a9cd80b" alt="Logo" width="50" height="50"> A GUI for Assistive Walking Exoskeleton
## 1. Introduction
This is an intuitive and effective Graphical User Interface for controlling an assistive walking exoskeleton for reabilitation. 

The interface is implemented in C++ with the aid of the Qt libraries for the graphics part and the connection to ROS. The main objective of the work was to develop a user-friendly interface so that the physiotherapist can focus on the patient and the effectiveness of the treatment. 

The validation of the interface was conducted through tests on a prototype exoskeleton, demonstrating its effectiveness and ease of use. 

## 2. Explanation of branches
- **main**: contains **only alice_pkg** (if you want to debug it setup will download also test branch) -> need to install manually the rosserial_python package
- **test**: contains **only fake_exo_pkg** in order to debug without the exoskeleton -> need to install manually both alice_pkg and rosserial_python packages
- **workspace**: contains **both the packages and rosserial_python** package (you don't need to install it)

## 3. Installation
If you have Windows 10 or 11 and want to run it, you must install wsl and install an Ubuntu-20.04 distribution by using prompt:
```
wsl --install -d Ubuntu-20.04
```
### 3.1 Download files
Open the terminal and clone the repo:
```
git clone https://github.com/cristianbass01/GUI_robotic_exoskeleton.git
```
or download the zip file and then decompress it:

```
wget https://github.com/cristianbass01/GUI_robotic_exoskeleton/archive/refs/heads/main.zip
unzip main.zip
```
If you don't have unzip installed:
```
sudo apt install unzip
```
Go to the repo directory created:
```
cd GUI_robotic_exoskeleton-main
```
Now you can put the alice_pkg package inside your workspace/src and the setup.sh file in the workspace directory.

### 3.2 Setup environment (only Ubuntu 20.04)
In order to be able to run this application, you need to have ROS Noetic installed on your system.
If not, you can install it using:
```
wget -c https://raw.githubusercontent.com/qboticslabs/ros_install_noetic/master/ros_install_noetic.sh && chmod +x ./ros_install_noetic.sh && ./ros_install_noetic.sh
```
If you have problems installing it, please refer to the official [ROS Noetic website](http://wiki.ros.org/noetic/Installation) for instructions.

After the installation of ROS noetic, you could make the setup.sh file executable:
```
chmod +x setup.sh
```

### 3.3 Launch file  
Now you can run setup.sh:
```
./setup.sh
```

A new launch.sh file is being created, run it:
```
./launch.sh
```

### 3.4 Debug Mode
It is possible to run the application in debug mode without the connection to the exoskeleton (just to test how it works)
Configurate the setup adding debug and run it:
```
./setup.sh debug
```

A new launch.sh file is being created, run it using debug (or not if you don't want the debug mode anymore):
```
./launch.sh debug
```

## 4. Authors
- Cristian Bassotto
- Nicola Busato
