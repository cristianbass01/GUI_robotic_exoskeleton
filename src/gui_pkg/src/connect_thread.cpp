#include "connect_thread.h"
#include <QtCore>

connectThread::connectThread(QObject *parent) :
    QThread(parent)
{
}

void connectThread::run(){
    while(true) {
        QMutex mutex;
        mutex.lock();
        if(this->Stop) break;
        if(!connectedComponent->isConnected())
            emit connectedComponent->connect();
        mutex.unlock();

        this->sleep(5);
    }
}
