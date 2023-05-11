#ifndef USERLIST_H
#define USERLIST_H

#include <QList>
#include <QFile>
#include <QXmlStreamWriter>
#include "user.h"

class UserList {
private:
  QList<User> userList;

public:
  UserList() {}
  void add(const User& user);
  void remove(const User& user);
  User* find(const QString& id);
  int findPos(const QString& id);
  User* getLast();
  void saveXml(const QString& fileName);
  void loadXml(const QString& fileName);
};

#endif // USERLIST_H
