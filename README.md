# <img src="https://github.com/cristianbass01/GUI_robotic_exoskeleton/assets/72708597/bb79ef7b-30f0-4e3a-9ffb-870d1a9cd80b" alt="Logo" width="50" height="50"> A GUI for Assistive Walking Exoskeleton
## 1. Introduction
This is an intuitive and effective Graphical User Interface for controlling an assistive walking exoskeleton for reabilitation. 

The interface is implemented in C++ with the aid of the Qt libraries for the graphics part and the connection to ROS. The main objective of the work was to develop a user-friendly interface so that the physiotherapist can focus on the patient and the effectiveness of the treatment. 

The validation of the interface was conducted through tests on a prototype exoskeleton, demonstrating its effectiveness and ease of use. 

## 2. Explanation of branches
- **main**: contains **only alice_pkg** (if you want to debug it setup will download also test branch) -> need to install manually the rosserial_python package
- **test**: contains **only fake_exo_pkg** in order to debug without the exoskeleton -> need to install manually both alice_pkg and rosserial_python packages
- **workspace**: contains **both the packages and rosserial_python** package (you don't need to install it)

## 3. Fake_exo_pkg
This is just a pkg to simulate the response of ALICE exoskeleton

In order to download the GUI go to main or workspace branch

## 4. Author
- Cristian Bassotto
