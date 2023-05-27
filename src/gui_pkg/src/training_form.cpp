#include "training_form.h"
#include "ui_training_form.h"

#include "session_form.h"

#include "main_form.h"

#include "step_form.h"
#include "control_form.h"
#include "walking_form.h"

TrainingForm::TrainingForm(FrameWindow *parent, User *user) :
  QWidget(parent),
  ui(new Ui::TrainingForm)
{
  frame_ = parent;
  user_ = user;
  ui->setupUi(this);

  this->displayUser();

  if(user == nullptr)
      log = nullptr;
  else
      log = new Log(user->getDir());
}

TrainingForm::~TrainingForm()
{
  delete ui;
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
    if(! connectedComponent->isConnected()){
        if(connectedComponent->connect())
            this->setConnected();
    }
}

void TrainingForm::setConnected(){
    ui->connectButton->setText("Connected");
    ui->connectButton->setStyleSheet("color: rgb(78, 154, 6); background-color: rgb(194, 251, 192)");
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
