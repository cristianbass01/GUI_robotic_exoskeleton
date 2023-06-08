#include "session_form.h"
#include "ui_session_form.h"

#include "training_form.h"
#include "step_form.h"
#include "walking_form.h"
#include "control_form.h"
#include "connected_component.h"

#include <global_variable.h>
#include <QTimer>
#include <QElapsedTimer>

SessionForm::SessionForm(FrameWindow *parent) :
    QWidget(parent),
    ui(new Ui::SessionForm)
{
    frame_ = parent;
    ui->setupUi(this);
    this->displayUser();

    ui->connectLoadingIcon->hide();

    this->setImage(this->NOTCONNECTED);

    // se è già attivo il timer vuol dire che la connessione è già in corso
    if(connectedComponent->timer_->isActive()){
        this->tryConnection();
        QObject::connect(connectedComponent->timer_.get(), SIGNAL(timeout()), this, SLOT(tryConnection()));
        connectedComponent->timer_->start(connectedComponent->CONTROL_TIME_OUT);
    }

}

SessionForm::~SessionForm()
{
    delete ui;
}

void SessionForm::on_controlButton_clicked()
{
    this->customizeForm(new ControlForm(this));
}


void SessionForm::on_stepButton_clicked()
{
    this->customizeForm(new StepForm(this));
}

void SessionForm::on_walkButton_clicked()
{
    this->customizeForm(new WalkingForm(this));
}

void SessionForm::on_returnButton_clicked()
{
    frame_->customizeWindow(new TrainingForm(frame_));
    frame_->show();

    this->close();
}

void SessionForm::customizeForm(QWidget *widget_to_insert){
    if(form_){
        ui->parentLayout->removeWidget(form_);
        form_->close();
    }

    ui->parentLayout->addWidget(widget_to_insert);

    if (widget_to_insert->objectName().compare("WalkingForm")==0){
        ui->walkButton->hide();
        ui->stepButton->show();
        ui->controlButton->show();
    } else if (widget_to_insert->objectName().compare("StepForm")==0) {
        ui->walkButton->show();
        ui->stepButton->hide();
        ui->controlButton->show();
    } else if (widget_to_insert->objectName().compare("ControlForm")==0) {
        ui->walkButton->show();
        ui->stepButton->show();
        ui->controlButton->hide();
    }

    form_ = widget_to_insert;
    changeStatus();
}

void SessionForm::changeStatus()
{
  if (form_->objectName().compare("WalkingForm")==0)
      qobject_cast<WalkingForm*>(form_)->setEnabled(status>1);
  else if (form_->objectName().compare("StepForm")==0)
      qobject_cast<StepForm*>(form_)->setEnabled(status>1);
  else if (form_->objectName().compare("ControlForm")==0)
      qobject_cast<ControlForm*>(form_)->setEnabled(status>1);
}


void SessionForm::on_connectButton_clicked()
{
    ui->connectLoadingIcon->show();
    QApplication::processEvents();

    this->tryConnection();

    ui->connectLoadingIcon->hide();
}

void SessionForm::tryConnection(){

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

void SessionForm::setConnected(bool state){
    if(state){
        if(ui->connectButton->text().toStdString().compare("Connected") != 0)
            this->setImage(this->STAND);
        ui->connectButton->setText("Connected");
        ui->connectButton->setStyleSheet("color: rgb(78, 154, 6); background-color: rgb(194, 251, 192);");
    }
    else {
        ui->connectButton->setText("Not connected\nPress to connect...");
        ui->connectButton->setStyleSheet("background-color: rgb(255, 213, 213); color: rgb(239, 41, 41);");
        this->setImage(this->NOTCONNECTED);
    }
    QCoreApplication::processEvents();

}

void SessionForm::displayUser(){
    if(currentUser){
        ui->userLabel->setText(currentUser->getName()+"  "+currentUser->getSurname());
    }
    else {
        ui->userLabel->setText("  Demo  ");
    }
}

void SessionForm::on_standButton_clicked()
{
    status = 2;
    changeStatus();
    frame_->showStatus("Standing...");
    this->movement(connectedComponent->STAND);
    frame_->clearStatus();
}

void SessionForm::on_sitButton_clicked()
{
    status = 1;
    changeStatus();
    frame_->showStatus("Sitting...");
    this->movement(connectedComponent->SIT);
    frame_->clearStatus();
}

void SessionForm::on_storageButton_clicked()
{
    status = 0;
    changeStatus();
    frame_->showStatus("Storing...");
    this->movement(connectedComponent->STORAGE);
    frame_->clearStatus();
}

void SessionForm::movement(const std::string code){
    this->setEnabled(false);

    form_->setEnabled(false);

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
            this->setImage(this->SIT);
            leg = "SIT";
            //close = true;
        } else if(code.compare(connectedComponent->STORAGE)== 0){
            this->setImage(this->STORAGE);
            leg = "STORAGE";
        } else if(code.compare(connectedComponent->STAND)== 0){
            this->setImage(this->STAND);
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
    form_->setEnabled(true);

    //addLog(leg, correct, close, t.addMSecs(ms));
}

void SessionForm::setEnabled(bool state){
    if (state){
        QApplication::restoreOverrideCursor();
        ui->sitButton->setEnabled(true);
        ui->storageButton->setEnabled(true);
        ui->standButton->setEnabled(true);
        ui->walkButton->setEnabled(true);
        ui->controlButton->setEnabled(true);
        ui->stepButton->setEnabled(true);
        ui->returnButton->setEnabled(true);
        frame_->setEnabled(true);
    } else {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        ui->sitButton->setEnabled(false);
        ui->storageButton->setEnabled(false);
        ui->standButton->setEnabled(false);
        ui->walkButton->setEnabled(false);
        ui->controlButton->setEnabled(false);
        ui->stepButton->setEnabled(false);
        ui->returnButton->setEnabled(false);
        frame_->setEnabled(false);
    }
}

void SessionForm::setImage(const QString code){
    QPixmap pixmap(code);
    int width = 400;
    int height = 400;
    QPixmap scaledPixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio);
    ui->Alice->setPixmap(scaledPixmap);
}
