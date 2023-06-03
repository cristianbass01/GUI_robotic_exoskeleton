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
  int size() { return userList.size();}
  void add(const User& user);
  void remove(const QString& id);
  User* find(const QString& id);
  int findPos(const QString& id);
  User* getAt(const int pos);
  User* getLast();
  void saveXml(const QString& fileName);
  void loadXml(const QString& fileName);
};

#endif // USERLIST_H
