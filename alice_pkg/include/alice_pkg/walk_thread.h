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
    /**
     * @brief WalkThread constructor
     * @param numSteps number of steps to make
     * @param log where to save logs
     */
    WalkThread(int numSteps, Log *log = nullptr);

    /**
     * @brief run start loop of steps that can be stopped after every single step
     *    -> upgrade progress bar after every step
     *    -> last step is leftclose
     *    -> control if the movement fails and execute a messagebox
     *    -> save logs after last step or stopped
     */
    void run();

    /**
     * @brief stop make stopped true
     */
    void stop();

private:
    /**
     * @brief numSteps_ number of steps to walk
     */
    int numSteps_;

    /**
     * @brief stopped_ if true the process is stopped
     */
    bool stopped_ = false;

    Log* log_;

signals:
    /**
     * @brief progressUpdated used to update a process in another class after every step (with QObject::connect())
     * @param value number of steps done
     */
    void progressUpdated(int value);

    /**
     * @brief stopped used to stop a process in another class when walking is finished
     */
    void stopped();

private slots:
    /**
     * @brief aggiunta del Log
     * @param set passi impostati
     * @param executed passi eseguiti
     * @param pause passi rimanenti dopo pause
     * @param time tempo rimaneto
     */
    void addLog(int set, int executed, int pause, QTime time);
};

#endif // WALK_THREAD_H
