#include "log.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <global_variable.h>

Log::Log(QString userDir){
    dir = path + userDir+ "/";
//    QDateTime date2 = QDateTime::currentDateTime();
//    date = date2.toString("ddMMyyyy");
    date= (QDateTime::currentDateTime()).toString("yyyyMMdd");
}

void Log::addWalkingEx(int set, int executed, int pause, QTime time)
{
  QString logMessage = QString("%1;%2;%3;%4").arg(set).arg(executed).arg(pause).arg(time.toString("hh:mm:ss:ms"));

  addToFile(QString("log_%1_WalkingEx").arg(date), logMessage);
  //addToFile("log_" + date + "_WalkingEx", set + ";" + executed + ";" + pause + ";" + time);
}

void Log::addStepEx(QString leg, bool correct, QTime time)
{
  QString logMessage = QString("%1;%2;%3").arg(leg).arg(correct).arg(time.toString("hh:mm:ss:ms"));

  addToFile(QString("log_%1_StepEx").arg(date), logMessage);
}

void Log::addToFile(QString fileName, QString log) // restituisce l'ultimo interno della prima colonna
{
  QFile file(dir + fileName);
  int nLine = 0;
  file.open(QIODevice::ReadWrite);
  QString line;
  QTextStream stream(&file);
  while( !stream.atEnd())
  {
      line = stream.readLine();
      nLine++;
  }
  int n = 0;
  if(nLine>0)
    n = line.split(";")[0].toInt();  // non us nLine, perchè nel caso venisse eliminata una riga dal file allora l'ultima verrebeb sovrascritta
  stream << QString::number(n) << ";" << log;
  file.close();
  //return nLine;
}
