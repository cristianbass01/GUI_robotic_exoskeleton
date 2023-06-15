#include "walk_thread.h"
#include "global_variable.h"
#include <QProgressBar>
#include <iostream>
#include "connected_component.h"
#include <QMutex>
#include <QTime>
#include <QElapsedTimer>

WalkThread::WalkThread(int numSteps, Log *log)
{
    this->numSteps_ = numSteps;
    log_ = log;
}

void WalkThread::run()
{
    QTime t = QTime(0,0,0);
    QElapsedTimer timer;
    timer.start();
    int step;
    for (step = 1; step <= numSteps_; ++step)
    {
        QMutex mutex;

        // Esegui un passo destro
        ConnectedComponent::getInstance().step(ConnectedComponent::getInstance().RIGHTSTEP);

        if(stopped_) break;

        mutex.lock();
        emit progressUpdated(step*2-1);
        mutex.unlock();

        sleep(1);

        if(step == numSteps_){
            ConnectedComponent::getInstance().step(ConnectedComponent::getInstance().LEFTCLOSE);

        }
        else{
            ConnectedComponent::getInstance().step(ConnectedComponent::getInstance().LEFTSTEP);
        }

        if(stopped_) break;

        mutex.lock();
        emit progressUpdated(step*2);
        mutex.unlock();

        sleep(1);
    }
    emit stopped();

    int ms = static_cast<int>(timer.elapsed());
    addLog(numSteps_,step -1, numSteps_ - (step - 1), t.addMSecs(ms));
}

void WalkThread::stop(){
    stopped_ = true;
}


void WalkThread::addLog(int set, int executed, int pause, QTime time){
    if(log_ != nullptr) // sono se non è in demo
        log_->addWalkingEx(set, executed, pause, time);
}
