#include "control_form.h"
#include "ui_control_form.h"
#include "global_variable.h"

#include <QObject>

ControlForm::ControlForm(SessionForm *parent, Log *log) :
    QWidget(parent),
    ui(new Ui::ControlForm)
{
    session_ = parent;
    frame_ = parent->getFrame();
    ui->setupUi(this);

    ui->stopButton->setEnabled(false);
    ui->progressBar->hide();

    log_ = log;
}

ControlForm::~ControlForm()
{
  delete log_;
}

void ControlForm::on_startButton_clicked()
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

            QObject::connect(thread_.get(), &WalkThread::progressUpdated, this, &ControlForm::updateProgressBar);
            QObject::connect(thread_.get(), &WalkThread::stopped, this, &ControlForm::finishProgressBar);
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

void ControlForm::on_stopButton_clicked()
{
    ui->stopButton->setText("Stopping...");
    ui->stopButton->setEnabled(false);

    if(thread_)
        thread_->stop();
}

void ControlForm::updateProgressBar(int value){
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

void ControlForm::finishProgressBar(){
    ui->progressBar->hide();

    ui->stopButton->setEnabled(false);
    ui->stopButton->setText("Stop");

    ui->startButton->setEnabled(true);
    session_->setEnabled(true);

    frame_->clearStatus();
}

void ControlForm::setEnabled(bool state){
    //ui->stopButton->setEnabled(state);
    ui->startButton->setEnabled(state);
}
