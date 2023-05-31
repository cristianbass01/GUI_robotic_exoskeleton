#include "walk_thread.h"
#include "global_variable.h"
#include <QProgressBar>
#include <iostream>
#include "connected_component.h"
#include <QMutex>

WalkThread::WalkThread(int numSteps)
{
    this->numSteps_ = numSteps;
}

void WalkThread::run()
{
    for (int step = 1; step <= numSteps_; ++step)
    {
        QMutex mutex;

        // Esegui un passo destro
        connectedComponent->step(connectedComponent->RIGHTSTEP);

        if(stopped_) break;

        mutex.lock();
        emit progressUpdated(step*2-1);
        mutex.unlock();

        sleep(1);

        if(step == numSteps_){
            connectedComponent->step(connectedComponent->LEFTCLOSE);

        }
        else{
            connectedComponent->step(connectedComponent->LEFTSTEP);
        }

        if(stopped_) break;

        mutex.lock();
        emit progressUpdated(step*2);
        mutex.unlock();

        sleep(1);
    }
    emit stopped();
}

void WalkThread::stop(){
    stopped_ = true;
}
