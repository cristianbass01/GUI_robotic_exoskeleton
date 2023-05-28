#include "training_form.h"
#include "ui_training_form.h"

#include "session_form.h"

#include "main_form.h"

#include "step_form.h"
#include "control_form.h"
#include "walking_form.h"

#include "global_variable.h"

#include <QObject>
#include <QCoreApplication>
#include <QTimer>

TrainingForm::TrainingForm(FrameWindow *parent, User *user) :
  QWidget(parent),
  ui(new Ui::TrainingForm)
{
  //frame_.reset(parent);
  //user_.reset(user);
  frame_ = parent;
  user_ = user;

  ui->setupUi(this);

  this->displayUser();
  currentUser = user;
  if(user == nullptr)
      log = nullptr;
  else
      log = new Log(user->getDir());

  // se è già attivo il timer vuol dire che la connessione è già in corso
  if(connectedComponent->timer_->isActive()){
      this->on_connectButton_clicked();
      QObject::connect(connectedComponent->timer_.get(), SIGNAL(timeout()), this, SLOT(on_connectButton_clicked()));
      connectedComponent->timer_->start(connectedComponent->CONTROL_TIME_OUT);
  }
}

TrainingForm::~TrainingForm()
{
  delete ui;
  delete frame_;
  delete log;
  delete user_;
}

void TrainingForm::on_standButton_clicked()
{

}

void TrainingForm::on_stepButton_clicked()
{
    SessionForm *session = new SessionForm(frame_);
    frame_->customizeWindow(session);

    //session->setWindowState(Qt::WindowMaximized);
    session->customizeForm(new StepForm(session, log));
}

void TrainingForm::on_walkButton_clicked()
{
    SessionForm *session = new SessionForm(frame_);
    frame_->customizeWindow(session);

    //session->setWindowState(Qt::WindowMaximized);
    session->customizeForm(new WalkingForm(session));
}

void TrainingForm::on_controlButton_clicked()
{
    SessionForm *session = new SessionForm(frame_);
    frame_->customizeWindow(session);

    //session->setWindowState(Qt::WindowMaximized);
    session->customizeForm(new ControlForm(session));
}

void TrainingForm::on_finishButton_clicked()
{

}

void TrainingForm::on_connectButton_clicked()
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

void TrainingForm::setConnected(bool state){
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

void TrainingForm::displayUser(){
    if(user_){
        ui->userLabel->setText(user_->getName()+" "+user_->getSurname());
    }
    else {
        ui->userLabel->setText("Demo");
    }
}
