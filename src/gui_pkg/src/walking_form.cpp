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

    log_ = log;
}

WalkingForm::~WalkingForm()
{
  delete log_;
}

void WalkingForm::on_startButton_clicked()
{
    ui->stopButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    session_->setEnabled(false);

    if (!ConnectedComponent::getInstance().isConnected())
        session_->on_connectButton_clicked();

    if(ConnectedComponent::getInstance().isConnected()){
        try {
            int numSteps = ui->walkingSteps->value();
            ui->progressBar->setRange(0, numSteps*2);
            ui->progressBar->setValue(0);
            ui->progressBar->show();

            thread_.reset(new WalkThread(numSteps, log_));
            thread_->start();

            QObject::connect(thread_.get(), &WalkThread::progressUpdated, this, &WalkingForm::updateProgressBar);
            QObject::connect(thread_.get(), &WalkThread::stopped, this, &WalkingForm::finishProgressBar);
        } catch (...) {
            ConnectedComponent::getInstance().errorMsg("Error while calling the service");
            session_->setEnabled(true);
            ui->stopButton->setEnabled(false);
            ui->startButton->setEnabled(true);
        }

    }
    else {
        ConnectedComponent::getInstance().errorMsg("Error while connecting to the service");
        session_->setConnected(false);
        session_->setEnabled(true);
        ui->stopButton->setEnabled(false);
        ui->startButton->setEnabled(true);
    }
}

void WalkingForm::on_stopButton_clicked()
{
    ui->stopButton->setText("Stopping...");
    ui->stopButton->setEnabled(false);

    if(thread_)
        thread_->stop();
}

void WalkingForm::updateProgressBar(int value){
    ui->progressBar->setValue(value);
    if(value%2 == 0){
        if(value == ui->progressBar->maximum()){
            frame_->showStatus("Walking: final step...");
        }
        else{
            frame_->showStatus("Walking: left step...");
        }
    } else {
        frame_->showStatus("Walking: right step...");
    }
    session_->updateImage();
}

void WalkingForm::finishProgressBar(){
    ui->progressBar->hide();

    ui->stopButton->setEnabled(false);
    ui->stopButton->setText("Stop");

    ui->startButton->setEnabled(true);
    session_->setEnabled(true);

    frame_->clearStatus();
}

void WalkingForm::setEnabled(bool state){
    //ui->stopButton->setEnabled(state);
    ui->startButton->setEnabled(state);
}
