#include "walking_form.h"
#include "ui_walking_form.h"
#include "global_variable.h"

#include <QObject>

WalkingForm::WalkingForm(SessionForm *parent, Log *log) :
    QWidget(parent),
    ui(new Ui::WalkingForm)
{
    session_ = parent;
    frame_ = parent->getFrame();
    ui->setupUi(this);

    ui->stopButton->setEnabled(false);
    ui->progressBar->hide();

    log_.reset(log);
}

WalkingForm::~WalkingForm()
{
}


void WalkingForm::addLog(int set, int executed, int pause, QTime time){
    if(log_ != nullptr) // sono in demo
    {
        log_->addWalkingEx(set, executed, pause, time);
    }
}

void WalkingForm::on_startButton_clicked()
{
    ui->stopButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    session_->setEnabled(false);

    if (!connectedComponent->isConnected())
        session_->on_connectButton_clicked();

    if(connectedComponent->isConnected()){
        //TODO Inserire un try catch per gestire la disconnessione durante la chiamata

        int numSteps = ui->walkingSteps->value();
        ui->progressBar->setRange(0, numSteps*2);
        ui->progressBar->setValue(0);
        ui->progressBar->show();

        thread_.reset(new WalkThread(numSteps));
        thread_->start();

        QObject::connect(thread_.get(), &WalkThread::progressUpdated, this, &WalkingForm::updateProgressBar);
        QObject::connect(thread_.get(), &WalkThread::stopped, this, &WalkingForm::finishProgressBar);
    }
    else {
        connectedComponent->errorMsg("Error while calling the service");
        session_->setConnected(false);
        session_->setEnabled(true);
        ui->stopButton->setEnabled(false);
        ui->startButton->setEnabled(true);
    }
}

void WalkingForm::on_stopButton_clicked()
{
    if(thread_)
        thread_->stop();
}

void WalkingForm::updateProgressBar(int value){
    ui->progressBar->setValue(value);
    if(value%2 == 0){
        if(value == ui->progressBar->maximum())
            session_->setImage(session_->LEFTCLOSE);
        else session_->setImage(session_->LEFTSTEP);
    } else session_->setImage(session_->RIGHTSTEP);
}

void WalkingForm::finishProgressBar(){
    ui->progressBar->hide();
    ui->stopButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    session_->setEnabled(true);
}
