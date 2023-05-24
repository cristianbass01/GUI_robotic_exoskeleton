#include "session_form.h"
#include "ui_session_form.h"

#include "training_form.h"
#include "step_form.h"
#include "walking_form.h"
#include "control_form.h"
#include "connected_component.h"

#include <global_variable.h>

SessionForm::SessionForm(FrameWindow *parent) :
    QWidget(parent),
    ui(new Ui::SessionForm)
{
    frame_ = parent;
    ui->setupUi(this);
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
    auto last = ui->parentLayout->takeAt(0);
    if(last != nullptr){
        ui->parentLayout->removeWidget(last->widget());
        last->widget()->close();
    }

    ui->parentLayout->addWidget(widget_to_insert);

    if (widget_to_insert->objectName().compare("WalkingForm")==0){
        frame_->setWindowTitle("Session - Walking");
        ui->walkWindowButton->hide();
        ui->stepWindowButton->show();
        ui->controlWindowButton->show();
    }else if (widget_to_insert->objectName().compare("StepForm")==0) {
        frame_->setWindowTitle("Session - Steps");
        ui->walkWindowButton->show();
        ui->stepWindowButton->hide();
        ui->controlWindowButton->show();
    } else if (widget_to_insert->objectName().compare("ControlForm")==0) {
        frame_->setWindowTitle("Session - Control Walking");
        ui->walkWindowButton->show();
        ui->stepWindowButton->show();
        ui->controlWindowButton->hide();
    }
}

void SessionForm::on_connectButton_clicked()
{
    if(! connectedComponent->isConnected()){
        connectedComponent->connect();
        this->setConnected();
    }
}

void SessionForm::setConnected(){
    ui->connectButton->setText("Connected");
    ui->connectButton->setStyleSheet("color: rgb(0, 255, 0);");
    QCoreApplication::processEvents();
}
