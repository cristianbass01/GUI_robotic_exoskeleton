#!/bin/bash

# Installa ROS Noetic (required)
# sudo apt install -y ros-noetic-desktop-full

# Inizializza l'ambiente di sviluppo di ROS Noetic
source /opt/ros/noetic/setup.bash

# Esegui catkin_make install
catkin_make install

# Controlla se il file ./install/lib/gui_pkg/start_gui_node esiste
if [ -f ./install/lib/gui_pkg/start_gui_node ]; then
    echo "Executable created. Now you can launch the launch.sh"
    echo "#!/bin/bash" > launch.sh
    echo "source /opt/ros/noetic/setup.bash \n ./install/lib/gui_pkg/start_gui_node" >> launch.sh
    
    # Rendi il file launch.sh eseguibile
    chmod +x launch.sh
else
    echo "Executable not created, retry."
fi
