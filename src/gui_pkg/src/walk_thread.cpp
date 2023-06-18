#include "walk_thread.h"
#include "global_variable.h"
#include <QProgressBar>
#include <iostream>
#include "connected_component.h"
#include <QMutex>
#include <QTime>
#include <QElapsedTimer>
#include <QMessageBox>

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
        if(!ConnectedComponent::getInstance().step(ConnectedComponent::getInstance().RIGHTSTEP)){
            break;
        }

        if(stopped_) break;

        mutex.lock();
        emit progressUpdated(step*2-1);
        mutex.unlock();

        if(step == numSteps_){
            if(!ConnectedComponent::getInstance().step(ConnectedComponent::getInstance().LEFTCLOSE)){
                break;
            }

        }
        else{
            if(!ConnectedComponent::getInstance().step(ConnectedComponent::getInstance().LEFTSTEP)){
                break;
            }
        }

        if(stopped_) break;

        mutex.lock();
        emit progressUpdated(step*2);
        mutex.unlock();
    }
    if(stopped_ == false && step-1 != numSteps_){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Movement failed");
        msgBox.setInformativeText("Exoskeleton failed the step");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        stopped_ = true;
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
