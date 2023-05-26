#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QDir>


class Log
{
private:
  QString date;
  QString dir;
  int nLineWalk, nLineStep;

  void addToFile(QString fileName, QString log);

public:
  Log() {}
  Log(QString dir);
  void addWalkingEx(int set, int executed, int pause, QTime time);
  void addStepEx(QString leg, bool correct, bool close, QTime time);
  void addControlEx(QString leg, bool correct, QTime time);
};

#endif // LOG_H
