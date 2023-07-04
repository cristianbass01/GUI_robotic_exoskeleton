#include "log.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <global_variable.h>

/**
 * @brief istanzia Log
 * @param dir Dove va salvato il file, percorso del utente
 */
Log::Log(QString userDir){
    dir = path + userDir+ "/"; // definisco la direcotry dove salvare i log
    date= (QDateTime::currentDateTime()).toString("yyyyMMdd"); // recupero il giorno attuale
}

/**
 * @brief Aggiunge Log per l'azione Walking
 * @param set Numero di passi impostati
 * @param executed Numero di passi eseguiti
 * @param pause Numero di passi rimanenti
 * @param time Tempo di esecuzione
 */
void Log::addWalkingEx(int set, int executed, int pause, QTime time)
{
  QString logMessage = QString("%1;%2;%3;%4").arg(set).arg(executed).arg(pause).arg(time.toString("hh:mm:ss:ms")); // trasformo i dati passati in stringa
  addToFile(QString("log%1_WalkingEx.log").arg(date), logMessage); // inserisco nel file
}

/**
 * @brief Aggiunge Log per l'azione Step
 * @param leg Gamba con cui è stata eseguito il movimento
 * @param count Numero del passo eseguito di seguito
 * @param correct Se il passo si è concluso correttamente
 * @param close Se il passo è di chiusura
 * @param time Tempo di esecuzione
 */
void Log::addStepEx(QString leg, int count, bool correct, bool close, QTime time)
{
  QString logMessage = QString("%1;%2;%3;%4;%5").arg(leg).arg(count).arg(correct).arg(close).arg(time.toString("hh:mm:ss:ms"));
  addToFile(QString("log%1_StepEx.log").arg(date), logMessage);
}

/**
 * @brief Aggiunge Log per l'azione Control
 * @param leg Gamba con cui è stata eseguito il movimento
 * @param correct Se il passo si è concluso correttamente
 * @param time Tempo di esecuzione
 */
void Log::addControlEx(QString leg, bool correct, QTime time)
{
  QString logMessage = QString("%1;%2;%3").arg(leg).arg(correct).arg(time.toString("hh:mm:ss:ms"));
  addToFile(QString("log%1_ControlEx.log").arg(date), logMessage);
}

/**
 * @brief Salva il log nel file
 * @param fileName Nome del file dove salvare il log
 * @param log Log da inserire
 */
void Log::addToFile(QString fileName, QString log)
{
  QFile file(dir + fileName); //recupera il file
  int nLine = 0;
  file.open(QIODevice::ReadWrite);
  QString line;
  QTextStream stream(&file);
  while( !stream.atEnd()) // legge l'ultimo intero presente
  {
      line = stream.readLine();
      nLine++;
  }
  int n = 0;
  if(nLine>0)
    n = line.split(";")[0].toInt();  // non us nLine, perchè nel caso venisse eliminata una riga dal file allora l'ultima verrebbe sovrascritta
  stream << QString::number(n + 1) << ";" << log << "\n"; //aggiungo numero di riga
  file.close();
}
