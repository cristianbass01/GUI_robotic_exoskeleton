#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include <user_list.h>
#include <QStandardPaths>
#include <QWidget>

#include "connected_component.h"
#include "connect_thread.h"

extern UserList userList;
extern const QString path;

extern std::shared_ptr<ConnectedComponent> connectedComponent;

extern std::shared_ptr<ConnectThread> connectThread;

#endif // GLOBAL_VARIABLE_H
