#include "user_list.h"
#include "user.h"

/**
 * @brief Aggiunge un utente alla lista degli utenti.
 * @param user L'utente da aggiungere.
 */
void UserList::add(const User& user) {
  int p = findPos(user.getId()); // cerco se l'utente è gia' presente
  if(p != -1) // se è presente allora lo modifico
  {
    userList[p].setName(user.getName());
    userList[p].setSurname(user.getSurname());
    userList[p].setBirthday(user.getBirthday());
    userList[p].setSex(user.getSex());
    userList[p].setHeight(user.getHeight());
    userList[p].setWeight(user.getWeight());
    userList[p].setUpperLeg(user.getUpperLeg());
    userList[p].setLowerLeg(user.getLowerLeg());
    return;
  }
  userList.append(user); // altrimenti aggiungo
}

/**
 * @brief Rimuove un utente dalla lista degli utenti dato l'ID.
 * @param id L'ID dell'utente da rimuovere.
 */
void UserList::remove(const QString& id) {
  int p = findPos(id);
  if(p>=0)
    userList.removeAt(p);
}

/**
 * @brief Trova un utente nella lista degli utenti dato l'ID.
 * @param id L'ID dell'utente da cercare.
 * @return Un puntatore all'utente trovato, o nullptr se non trovato.
 */
User* UserList::find(const QString& id) {
  foreach (const User& user, userList) {
    if (user.getId() == id) {
      return const_cast<User*>(&user);
    }
  }
  return nullptr;
}

/**
 * @brief Trova la posizione di un utente nella lista degli utenti dato l'ID.
 * @param id L'ID dell'utente da cercare.
 * @return La posizione dell'utente trovato, o -1 se non trovato.
 */
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

/**
 * @brief Restituisce un puntatore all'utente nella lista dato l'indice.
 * @param pos L'indice dell'utente da restituire.
 * @return Un puntatore all'utente, o nullptr se l'indice è fuori dai limiti.
 */
User* UserList::getAt(const int pos){
  if(pos >= 0 && pos < userList.size())
    return &userList[pos];
  return nullptr;
}

/**
 * @brief Restituisce un puntatore all'ultimo utente nella lista.
 * @return Un puntatore all'ultimo utente, o nullptr se la lista è vuota.
 */
User* UserList::getLast() {
  if (userList.isEmpty()) {
    // lista vuota, restituisce un utente vuoto
    return nullptr;
  }
  return &userList.last();
}

/**
 * @brief Salva la lista degli utenti in un file XML.
 * @param fileName Il nome del file XML in cui salvare la lista degli utenti.
 */
void UserList::saveXml(const QString& fileName) {
  QFile xmlFile(fileName);
  if (!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    // gestione dell'errore
    return;
  }

  //salvataggio su xml
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
    xmlWriter.writeAttribute("upperLeg", QString::number(user.getUpperLeg()));
    xmlWriter.writeAttribute("LowerLeg", QString::number(user.getLowerLeg()));
    xmlWriter.writeEndElement();
    }

  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();
  xmlFile.close();
}

/**
 * @brief Carica la lista degli utenti da un file XML.
 * @param fileName Il nome del file XML da cui caricare la lista degli utenti.
 */
void UserList::loadXml(const QString& fileName) {
  QFile xmlFile(fileName);
  if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    // gestione dell'errore
    return;
  }

  //caricamento da xml
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
        currentUser.setUpperLeg(attributes.value("upperLeg").toInt());
        currentUser.setLowerLeg(attributes.value("lowerLeg").toInt());
        userList.append(currentUser);
      }
    }
  }

  if (xmlReader.hasError()) {
    // eventuale gestione dell'errore
  }

  xmlFile.close();
}
