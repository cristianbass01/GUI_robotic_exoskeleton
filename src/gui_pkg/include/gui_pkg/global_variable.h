#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include <user_list.h>
#include <QStandardPaths>
#include <QWidget>

#include "connected_component.h"

extern UserList userList;
extern User* currentUser;
extern const QString path;
extern int status; // 0 storage; 1 sit; 2 stand; 3 moving

#endif // GLOBAL_VARIABLE_H
