#ifndef WALK_THREAD_H
#define WALK_THREAD_H

#include <QApplication>
#include <QThread>
#include <QProgressBar>
#include <QSharedPointer>

class WalkThread : public QThread
{
    Q_OBJECT
public:
    WalkThread(int numSteps);

    void run();

    void stop();
private:
    int numSteps_;
    bool stopped_ = false;
signals:
    void progressUpdated(int value);
    void stopped();

public slots:
};

#endif // WALK_THREAD_H
