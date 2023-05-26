#ifndef CONNECT_THREAD_H
#define CONNECT_THREAD_H

#include <QThread>
#include "connected_component.h"
#include "global_variable.h"

class connectThread : public QThread
{
    Q_OBJECT
public:
    explicit connectThread(QObject *parent = nullptr);
    void run();
    bool Stop;

signals:

public slots:

};

#endif // CONNECT_THREAD_H
