#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QDir>

/**
 * @brief Classe per la gestione dei log
 */
class Log
{
private:
  QString date;
  QString dir;

  /**
   * @brief Salva il log nel file
   * @param fileName Nome del file dove salvare il log
   * @param log Log da inserire
   */
  void addToFile(QString fileName, QString log);

public:

  /**
   * @brief istanzia Log
   * @param dir Dove va salvato il file, percorso del utente
   */
  Log(QString dir);

  /**
   * @brief Aggiunge Log per l'azione Walking
   * @param set Numero di passi impostati
   * @param executed Numero di passi eseguiti
   * @param pause Numero di passi rimanenti
   * @param time Tempo di esecuzione
   */
  void addWalkingEx(int set, int executed, int pause, QTime time);

  /**
   * @brief Aggiunge Log per l'azione Step
   * @param leg Gamba con cui è stata eseguito il movimento
   * @param count Numero del passo eseguito di seguito
   * @param correct Se il passo si è concluso correttamente
   * @param close Se il passo è di chiusura
   * @param time Tempo di esecuzione
   */
  void addStepEx(QString leg, int count, bool correct, bool close, QTime time);

  /**
   * @brief Aggiunge Log per l'azione Control
   * @param leg Gamba con cui è stata eseguito il movimento
   * @param correct Se il passo si è concluso correttamente
   * @param time Tempo di esecuzione
   */
  void addControlEx(QString leg, bool correct, QTime time);
};

#endif // LOG_H
