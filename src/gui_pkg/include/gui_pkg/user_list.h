#ifndef USERLIST_H
#define USERLIST_H

#include <QList>
#include <QFile>
#include <QXmlStreamWriter>
#include "user.h"

/**
 * @brief Classe UserList per gestire la lista di utenti associata al Esosheletro.
 */
class UserList {
private:
  QList<User> userList; /**< Lista degli utenti */

public:
  /**
   * @brief Costruttore di default per la classe UserList.
   */
  UserList() {}

  /**
   * @brief Restituisce la dimensione della lista degli utenti.
   * @return La dimensione della lista degli utenti.
   */
  int size() { return userList.size(); }

  /**
   * @brief Aggiunge un utente alla lista degli utenti.
   * @param user L'utente da aggiungere.
   */
  void add(const User& user);

  /**
   * @brief Rimuove un utente dalla lista degli utenti dato l'ID.
   * @param id L'ID dell'utente da rimuovere.
   */
  void remove(const QString& id);

  /**
   * @brief Trova un utente nella lista degli utenti dato l'ID.
   * @param id L'ID dell'utente da cercare.
   * @return Un puntatore all'utente trovato, o nullptr se non trovato.
   */
  User* find(const QString& id);

  /**
   * @brief Trova la posizione di un utente nella lista degli utenti dato l'ID.
   * @param id L'ID dell'utente da cercare.
   * @return La posizione dell'utente trovato, o -1 se non trovato.
   */
  int findPos(const QString& id);

  /**
   * @brief Restituisce un puntatore all'utente nella lista dato l'indice.
   * @param pos L'indice dell'utente da restituire.
   * @return Un puntatore all'utente, o nullptr se l'indice è fuori dai limiti.
   */
  User* getAt(const int pos);

  /**
   * @brief Restituisce un puntatore all'ultimo utente nella lista.
   * @return Un puntatore all'ultimo utente, o nullptr se la lista è vuota.
   */
  User* getLast();

  /**
   * @brief Salva la lista degli utenti in un file XML.
   * @param fileName Il nome del file XML in cui salvare la lista degli utenti.
   */
  void saveXml(const QString& fileName);

  /**
   * @brief Carica la lista degli utenti da un file XML.
   * @param fileName Il nome del file XML da cui caricare la lista degli utenti.
   */
  void loadXml(const QString& fileName);
};

#endif // USERLIST_H
