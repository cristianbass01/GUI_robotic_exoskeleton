#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include <user_list.h>
#include <QStandardPaths>
#include <QWidget>

#include "connected_component.h"

extern UserList userList;  // lista degli utenti
extern User* currentUser;  // utente attualmente selezionato
extern const QString path; // directory dove vengono salvati i commenti
//! l'assegnamento avviene nel file nodes/start_gui_node

#endif // GLOBAL_VARIABLE_H
