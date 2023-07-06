#!/bin/bash

# Installa ROS Noetic (required)
# sudo apt install -y ros-noetic-desktop-full

# Inizializza l'ambiente di sviluppo di ROS Noetic
source /opt/ros/noetic/setup.bash

if [ "$1" == "debug" ]; then
    if [ ! -d ./src/fake_exo_pkg ]; then
    	echo "Downloading Test package fake_exo..."
    	wget https://github.com/cristianbass01/GUI_robotic_exoskeleton/archive/refs/heads/test.zip
    	
    	echo "Unzipping file"
    	unzip test.zip
    	
    	echo "Moving directory"
    	mv ./GUI_robotic_exoskeleton-test/fake_exo ./src/fake_exo_pkg
   	
    	rm -r ./GUI_robotic_exoskeleton-test
    	rm test.zip
    fi
fi

# Esegui catkin_make install
catkin_make install

# Controlla se il file ./install/lib/alice_pkg/start_gui_node esiste
if [ -f ./install/lib/alice_pkg/start_gui_node ]; then
    echo "Executable created. Now you can launch the launch.sh"
    echo "#!/bin/bash
source ./devel/setup.sh

if [ \"\$1\" == \"debug\" ]; then
    echo \"Running application in debug node...\"
    # Comando per avviare l'applicazione in modalità debug
    
    # Controllo se che fake_exo sia già compilato
    if [ -f ./install/lib/fake_exo/exoskeleton_node ]; then
    	./install/lib/alice_pkg/start_gui_node debug
    else
    	echo \"Fake_exo not compiled. Execute './setup.sh debug' in order to debug\"
    fi
  else
    echo \"Running application...\"
    # Comando per avviare l'applicazione normale
    ./install/lib/alice_pkg/start_gui_node
  fi
" > launch.sh
    
    # Rendi il file launch.sh eseguibile
    chmod +x launch.sh
else
    echo "Executable not created, retry."
fi
