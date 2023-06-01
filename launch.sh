#!/bin/bash

if [ -f ./install/lib/gui_pkg/start_gui_node ]
	then
		echo file trovato
		./install/lib/gui_pkg/start_gui_node
	else
		echo file non trovato
fi
