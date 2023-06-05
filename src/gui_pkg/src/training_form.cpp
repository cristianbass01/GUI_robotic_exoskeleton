#include "training_form.h"
#include "ui_training_form.h"

#include "session_form.h"

#include "main_form.h"

#include "step_form.h"
#include "control_form.h"
#include "walking_form.h"

#include "global_variable.h"

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

TrainingForm::TrainingForm(FrameWindow *parent) :
  QWidget(parent),
  ui(new Ui::TrainingForm)
{
  frame_ = parent;

  ui->setupUi(this);
  ui->connectLoadingIcon->hide();

  this->displayUser();

  // se è già attivo il timer vuol dire che la connessione è già in corso
  if(connectedComponent->timer_->isActive()){
      this->tryConnection();
      QObject::connect(connectedComponent->timer_.get(), SIGNAL(timeout()), this, SLOT(tryConnection()));
      connectedComponent->timer_->start(connectedComponent->CONTROL_TIME_OUT);
  }
}

TrainingForm::~TrainingForm()
{
    delete ui;
}

void TrainingForm::on_standButton_clicked()
{
    frame_->showStatus("Standing...");
    this->movement(connectedComponent->STAND);
    frame_->clearStatus();
}

void TrainingForm::on_sitButton_clicked()
{
    frame_->showStatus("Sitting...");
    this->movement(connectedComponent->SIT);
    frame_->clearStatus();
}

void TrainingForm::on_storageButton_clicked()
{
    frame_->showStatus("Storing...");
    this->movement(connectedComponent->STORAGE);
    frame_->clearStatus();
}

void TrainingForm::on_stepButton_clicked()
{
    SessionForm *session = new SessionForm(frame_);
    frame_->customizeWindow(session);

    //session->setWindowState(Qt::WindowMaximized);
    session->customizeForm(new StepForm(session, createLog()));
}

void TrainingForm::on_walkButton_clicked()
{
    SessionForm *session = new SessionForm(frame_);
    frame_->customizeWindow(session);

    //session->setWindowState(Qt::WindowMaximized);
    session->customizeForm(new WalkingForm(session, createLog()));
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
    QApplication::quit();
}

void TrainingForm::on_connectButton_clicked()
{
    ui->connectLoadingIcon->show();
    frame_->showStatus("Connecting...");
    QApplication::processEvents();

    this->tryConnection();

    ui->connectLoadingIcon->hide();
    frame_->clearStatus();
}

void TrainingForm::tryConnection(){
    if(connectedComponent->connect()){
        this->setConnected(true);
        if(! connectedComponent->timer_->isActive()){
            QObject::connect(connectedComponent->timer_.get(), SIGNAL(timeout()), this, SLOT(tryConnection()));
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
    if(currentUser){
        ui->userLabel->setText(currentUser->getName()+"  "+currentUser->getSurname());
    }
    else {
        ui->userLabel->setText("  Demo  ");
    }
}

void TrainingForm::movement(const std::string code){
    this->setEnabled(false);

    //this->customizeForm(qobject_cast<StepForm*>(ui->parentLayout->takeAt(0)->widget()));
    QCoreApplication::processEvents();

    // LOG
    QString leg;
    bool correct = true, close = false;
    //QTime t = QTime(0,0,0);
    int ms = 0;
    //--
    if (!connectedComponent->isConnected())
        this->on_connectButton_clicked();

    if (connectedComponent->isConnected()){
        //TODO Inserire un try catch per gestire la disconnessione durante la chiamata
        QElapsedTimer timer;
        timer.start();
        connectedComponent->step(code);
        if(code.compare(connectedComponent->SIT) == 0){
            leg = "SIT";
            //close = true;
        } else if(code.compare(connectedComponent->STORAGE)== 0){
            leg = "STORAGE";
        } else if(code.compare(connectedComponent->STAND)== 0){
            leg = "STAND";
        }
        ms = static_cast<int>(timer.elapsed());
        //timer.stop();
        //Qint milliseconds = 1500;  // Esempio di tempo in millisecondi
    }
    else {
        connectedComponent->errorMsg("Error while calling the service");
        this->setConnected(false);
        correct = false;
    }

    this->setEnabled(true);

    //addLog(leg, correct, close, t.addMSecs(ms));
}

void TrainingForm::setEnabled(bool state){

    if (state){
        QApplication::restoreOverrideCursor();
        ui->sitButton->setEnabled(true);
        ui->storageButton->setEnabled(true);
        ui->standButton->setEnabled(true);
        ui->stepButton->setEnabled(true);
        ui->walkButton->setEnabled(true);
        ui->controlButton->setEnabled(true);
    } else {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        ui->sitButton->setEnabled(false);
        ui->storageButton->setEnabled(false);
        ui->standButton->setEnabled(false);
        ui->stepButton->setEnabled(false);
        ui->walkButton->setEnabled(false);
        ui->controlButton->setEnabled(false);
    }
}

Log* TrainingForm::createLog() // troppo un casino con log condiviso in caso de delete
{
  if(currentUser == nullptr)
      return nullptr;
  else
      return new Log(currentUser->getDir());
}
