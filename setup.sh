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
    echo "#!/bin/bash
source ./devel/setup.sh

if [ \"\$1\" == \"debug\" ]; then
    echo \"Avvio dell'applicazione in modalità debug...\"
    # Comando per avviare l'applicazione in modalità debug
    ./install/lib/gui_pkg/start_gui_node debug
  else
    echo \"Avvio dell'applicazione...\"
    # Comando per avviare l'applicazione normale
    ./install/lib/gui_pkg/start_gui_node
  fi
" >> launch.sh
    
    # Rendi il file launch.sh eseguibile
    chmod +x launch.sh
else
    echo "Executable not created, retry."
fi
