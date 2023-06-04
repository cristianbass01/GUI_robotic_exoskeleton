#include "step_form.h"
#include "ui_step_form.h"

#include "session_form.h"

#include "connected_component.h"
#include <global_variable.h>
#include <QMovie>
#include <QTimer>
#include <QElapsedTimer>

StepForm::StepForm(SessionForm *parent, Log *log) :
    QWidget(parent),
    ui(new Ui::StepForm)
{
    session_ = parent;
    frame_ = parent->getFrame();
    ui->setupUi(this);

    log_ = log;
    stepCount = 1;
}

StepForm::~StepForm()
{
    delete ui;
    delete log_;
}

void StepForm::on_leftFirstStepButton_clicked()
{
    this->movement(connectedComponent->LEFTSTEP);
}

void StepForm::on_rightFirstStepButton_clicked()
{
    this->movement(connectedComponent->RIGHTSTEP);
}

void StepForm::on_feetTogetherButton_clicked()
{
    this->movement(connectedComponent->LEFTCLOSE);
}

void StepForm::movement(const std::string code){
    this->setEnabled(false);
    session_->setEnabled(false);

    ui->loadingLabel->setMargin(0);
    ui->loadingLabel->setText("<img src=\":/icons/Icons/update-left-rotation.png\" width=\"40\"/>");

    QCoreApplication::processEvents();

    // LOG
    QString leg;
    bool correct = true, close = false;
    QTime t = QTime(0,0,0);
    int ms = 0;
    //--

    if (!connectedComponent->isConnected())
        session_->on_connectButton_clicked();

    if (connectedComponent->isConnected()){
        //TODO Inserire un try catch per gestire la disconnessione durante la chiamata
        try {
            QElapsedTimer timer;
            timer.start();

            connectedComponent->step(code);
            this->lastStep = code;

            QApplication::processEvents();

            this->setEnabled(true);
            session_->setEnabled(true);

            if(code.compare(connectedComponent->LEFTCLOSE) == 0){
                session_->setImage(session_->LEFTCLOSE);
                leg = "LEFT";
                close = true;
            } else if(code.compare(connectedComponent->LEFTSTEP)== 0){
                session_->setImage(session_->LEFTSTEP);
                leg = "LEFT";
            } else if(code.compare(connectedComponent->RIGHTSTEP)== 0){
                session_->setImage(session_->RIGHTSTEP);
                leg = "RIGHT";
            }
            ms = static_cast<int>(timer.elapsed());
            //timer.stop();
            //Qint milliseconds = 1500;  // Esempio di tempo in millisecondi

            ui->loadingLabel->setText("");
            ui->loadingLabel->setMargin(9);
        } catch (...) {
            connectedComponent->errorMsg("Error while calling the service");
        }

    }
    else {
        connectedComponent->errorMsg("Error during the connection to the service");
        session_->setConnected(false);
        correct = false;
        this->setEnabled(true);
        session_->setEnabled(true);
    }
    addLog(leg, correct, close, t.addMSecs(ms));
}

void StepForm::addLog(QString leg, bool correct, bool close, QTime time)
{
    if(log_ != nullptr) // sono in demo
    {
        stepCount++;
        log_->addStepEx(leg, correct, close, time);
        if(close)
            stepCount = 1;
    }
}

void StepForm::setEnabled(bool state){
    if (!state){
        ui->feetTogetherButton->setEnabled(false);
        ui->leftFirstStepButton->setEnabled(false);
        ui->rightFirstStepButton->setEnabled(false);
    }
    else {
        if(lastStep.size() > 0){
            if(lastStep.compare(connectedComponent->LEFTCLOSE) == 0){
                ui->leftFirstStepButton->setEnabled(true);
                ui->rightFirstStepButton->setEnabled(true);
            } else if(lastStep.compare(connectedComponent->LEFTSTEP) == 0){
                ui->rightFirstStepButton->setEnabled(true);
            } else if(lastStep.compare(connectedComponent->RIGHTSTEP) == 0){
                ui->feetTogetherButton->setEnabled(true);
                ui->leftFirstStepButton->setEnabled(true);
            }
        }
        else{
            ui->leftFirstStepButton->setEnabled(true);
            ui->rightFirstStepButton->setEnabled(true);
        }
    }
}
