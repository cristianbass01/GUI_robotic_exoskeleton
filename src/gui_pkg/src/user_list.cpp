#include "user_list.h"
#include "user.h"

void UserList::add(const User& user) {
  int p = findPos(user.getId());
  if(p != -1)
  {
    userList[p].setName(user.getName());
    userList[p].setSurname(user.getSurname());
    userList[p].setBirthday(user.getBirthday());
    userList[p].setSex(user.getSex());
    userList[p].setHeight(user.getHeight());
    userList[p].setWeight(user.getWeight());
    userList[p].setFemur(user.getFemur());
    userList[p].setTibia(user.getTibia());
    return;
  }
  userList.append(user);
}

void UserList::remove(const User& user) {
  int p = findPos(user.getId());
  if(p>=0)
    userList.removeAt(p);
}

User* UserList::find(const QString& id) {
  foreach (const User& user, userList) {
    if (user.getId() == id) {
      return const_cast<User*>(&user);
    }
  }
  return nullptr;
}

int UserList::findPos(const QString& id) {
  int pos = 0;
  foreach (User user, userList) {
    if (user.getId() == id) {
      return pos;
    }
    pos++;
  }
  return -1;
}

User* UserList::getAt(const int pos){
  if(pos >= 0 && pos < userList.size())
    return &userList[pos];
  return nullptr;
}

User* UserList::getLast() {
  if (userList.isEmpty()) {
    // lista vuota, restituisce un utente vuoto
    return nullptr;
  }
  return &userList.last();
}

void UserList::saveXml(const QString& fileName) {
  QFile xmlFile(fileName);
  if (!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    // gestione dell'errore
    return;
  }

  QXmlStreamWriter xmlWriter(&xmlFile);
  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();

  // scrittura degli utenti nel file XML
  xmlWriter.writeStartElement("users");

  foreach (const User& user, userList) {
    xmlWriter.writeStartElement("user");
    xmlWriter.writeAttribute("dir", user.getDir());
    xmlWriter.writeAttribute("id", user.getId());
    xmlWriter.writeAttribute("name", user.getName());
    xmlWriter.writeAttribute("surname", user.getSurname());
    xmlWriter.writeAttribute("birthday", user.getBirthday().toString("yyyy-MM-dd"));
    xmlWriter.writeAttribute("sex", user.getSex());
    xmlWriter.writeAttribute("height", QString::number(user.getHeight()));
    xmlWriter.writeAttribute("weight", QString::number(user.getWeight()));
    xmlWriter.writeAttribute("femur", QString::number(user.getFemur()));
    xmlWriter.writeAttribute("tibia", QString::number(user.getTibia()));
    xmlWriter.writeEndElement();
    }

  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();
  xmlFile.close();
}

void UserList::loadXml(const QString& fileName) {
  QFile xmlFile(fileName);
  if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    // gestione dell'errore
    return;
  }

  QXmlStreamReader xmlReader(&xmlFile);

  User currentUser;
  QString currentElementName;

  while (!xmlReader.atEnd()) {
    xmlReader.readNext();

    if (xmlReader.isStartElement()) {
      if (xmlReader.name() == "user") {
        currentUser = User();
        QXmlStreamAttributes attributes = xmlReader.attributes();
        currentUser.setDir(attributes.value("dir").toString());
        currentUser.setId(attributes.value("id").toString());
        currentUser.setName(attributes.value("name").toString());
        currentUser.setSurname(attributes.value("surname").toString());
        currentUser.setBirthday(QDate::fromString(attributes.value("birthday").toString(), "yyyy-MM-dd"));
        currentUser.setSex(attributes.value("sex").toString());
        currentUser.setHeight(attributes.value("height").toInt());
        currentUser.setWeight(attributes.value("weight").toInt());
        currentUser.setFemur(attributes.value("femur").toInt());
        currentUser.setTibia(attributes.value("tibia").toInt());
        userList.append(currentUser);
      }
    }
  }

  if (xmlReader.hasError()) {
    // gestione dell'errore
  }

  xmlFile.close();
}
