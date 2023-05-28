#include "session_form.h"
#include "ui_session_form.h"

#include "training_form.h"
#include "step_form.h"
#include "walking_form.h"
#include "control_form.h"
#include "connected_component.h"

#include <global_variable.h>

SessionForm::SessionForm(FrameWindow *parent, User *user) :
    QWidget(parent),
    ui(new Ui::SessionForm)
{
    frame_.reset(parent);
    user_.reset(user);
    ui->setupUi(this);
    this->displayUser();

    // se è già attivo il timer vuol dire che la connessione è già in corso
    if(connectedComponent->timer_->isActive()){
        this->on_connectButton_clicked();
        QObject::connect(connectedComponent->timer_.get(), SIGNAL(timeout()), this, SLOT(on_connectButton_clicked()));
        connectedComponent->timer_->start(connectedComponent->CONTROL_TIME_OUT);
    }

}

SessionForm::~SessionForm()
{
    delete ui;
}

void SessionForm::on_controlWindowButton_clicked()
{
    this->customizeForm(new ControlForm(this));
}


void SessionForm::on_stepWindowButton_clicked()
{
    this->customizeForm(new StepForm(this));
}

void SessionForm::on_walkWindowButton_clicked()
{
    this->customizeForm(new WalkingForm(this));
}

void SessionForm::on_returnButton_clicked()
{
    frame_->customizeWindow(new TrainingForm(frame_.get()));
    frame_->show();

    this->close();
}

void SessionForm::customizeForm(QWidget *widget_to_insert){
    auto last = ui->parentLayout->takeAt(0);
    if(last != nullptr){
        ui->parentLayout->removeWidget(last->widget());
        last->widget()->close();
    }

    ui->parentLayout->addWidget(widget_to_insert);

    if (widget_to_insert->objectName().compare("WalkingForm")==0){
        ui->walkWindowButton->hide();
        ui->stepWindowButton->show();
        ui->controlWindowButton->show();
    } else if (widget_to_insert->objectName().compare("StepForm")==0) {
        ui->walkWindowButton->show();
        ui->stepWindowButton->hide();
        ui->controlWindowButton->show();
    } else if (widget_to_insert->objectName().compare("ControlForm")==0) {
        ui->walkWindowButton->show();
        ui->stepWindowButton->show();
        ui->controlWindowButton->hide();
    }
}

void SessionForm::on_connectButton_clicked()
{
    if(connectedComponent->connect()){
        this->setConnected(true);
        if(! connectedComponent->timer_->isActive()){
            QObject::connect(connectedComponent->timer_.get(), SIGNAL(timeout()), this, SLOT(on_connectButton_clicked()));
            connectedComponent->timer_->start(connectedComponent->CONTROL_TIME_OUT);
        }
    }
    else {
        this->setConnected(false);
        if(connectedComponent->timer_->isActive())
            connectedComponent->timer_->stop();
    }
}

void SessionForm::setConnected(bool state){
    if(state){
        ui->connectButton->setText("Connected");
        ui->connectButton->setStyleSheet("color: rgb(78, 154, 6); background-color: rgb(194, 251, 192);");
    }
    else {
        ui->connectButton->setText("Not connected\nPress to connect...");
        ui->connectButton->setStyleSheet("background-color: rgb(255, 213, 213); color: rgb(239, 41, 41);");
    }
    QCoreApplication::processEvents();

}

void SessionForm::displayUser(){
    if(user_){
        ui->userLabel->setText(user_->getName()+" "+user_->getSurname());
    }
    else {
        ui->userLabel->setText("Demo");
    }
}
