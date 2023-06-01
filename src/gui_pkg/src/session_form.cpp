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

SessionForm::SessionForm(FrameWindow *parent, User *user) :
    QWidget(parent),
    ui(new Ui::SessionForm)
{
    frame_ = parent;
    user_ = user;
    ui->setupUi(this);
    this->displayUser();

    ui->connectLoadingIcon->hide();

    this->setImage(this->NOTCONNECTED);

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

    form_ = widget_to_insert;
}

void SessionForm::on_connectButton_clicked()
{
    ui->connectLoadingIcon->show();
    QApplication::processEvents();

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
    ui->connectLoadingIcon->hide();
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
    if(user_){
        ui->userLabel->setText(user_->getName()+" "+user_->getSurname());
    }
    else {
        ui->userLabel->setText("Demo");
    }
}

void SessionForm::on_standButton_clicked()
{
    this->movement(connectedComponent->STAND);
}

void SessionForm::on_sitButton_clicked()
{
    this->movement(connectedComponent->SIT);
}

void SessionForm::on_storageButton_clicked()
{
    this->movement(connectedComponent->STORAGE);
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
        ui->sitButton->setEnabled(true);
        ui->storageButton->setEnabled(true);
        ui->standButton->setEnabled(true);
    } else {
        ui->sitButton->setEnabled(false);
        ui->storageButton->setEnabled(false);
        ui->standButton->setEnabled(false);
    }
}

void SessionForm::setImage(const QString code){
    QPixmap pixmap(code);
    int width = 400;
    int height = 400;
    QPixmap scaledPixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio);
    ui->Alice->setPixmap(scaledPixmap);
}
