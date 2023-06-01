# <img src="https://github.com/cristianbass01/GUI_robotic_exoskeleton/assets/72708597/bb79ef7b-30f0-4e3a-9ffb-870d1a9cd80b" alt="Logo" width="50" height="50"> A GUI for Assistive Walking Exoskeleton
## 1. Introduction
This is an intuitive and effective Graphical User Interface for controlling an assistive walking exoskeleton for reabilitation. 

The interface is implemented in C++ with the aid of the Qt libraries for the graphics part and the connection to ROS. The main objective of the work was to develop a user-friendly interface so that the physiotherapist can focus on the patient and the effectiveness of the treatment. 

The validation of the interface was conducted through tests on a prototype exoskeleton, demonstrating its effectiveness and ease of use. 

In summary, the developed interface represents an innovative and effective solution for the control of exoskeletons, offering a new possibility of customisation and control to improve the quality of life of patients requiring walking assistance.


## 2. Installation on Ubuntu
### Download files
Open the terminal and clone the repo:
```
$ git clone https://github.com/cristianbass01/GUI_robotic_exoskeleton.git
```
or download the zip file and then decompress it:

```
$ wget https://github.com/cristianbass01/GUI_robotic_exoskeleton/archive/refs/heads/main.zip
$ unzip main.zip -d ./GUI_exoskeleton
```
Go to the repo directory created:
```
$ cd GUI_robotic_exoskeleton 
```
  
### Setup environment
Make the setup.sh file executable and run it:
```
$ chmod +x setup.sh
$ ./setup.sh
```
### Launch file  
A new launch.sh file is being created, run it:
```
$ ./launch.sh
```

## 3. Authors
- Cristian Bassotto
- Nicola Busato
