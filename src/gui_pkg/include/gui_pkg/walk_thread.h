#ifndef WALK_THREAD_H
#define WALK_THREAD_H

#include <QApplication>
#include <QThread>
#include <QProgressBar>
#include <QSharedPointer>
#include <log.h>

class WalkThread : public QThread
{
    Q_OBJECT
public:
    WalkThread(int numSteps, Log *log = nullptr);

    void run();

    void stop();
private:
    int numSteps_;
    bool stopped_ = false;

    Log* log_;

signals:
    void progressUpdated(int value);
    void stopped();

private slots:
    void addLog(int set, int executed, int pause, QTime time);
};

#endif // WALK_THREAD_H
