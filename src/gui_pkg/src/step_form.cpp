#include "step_form.h"
#include "ui_step_form.h"

#include "session_form.h"

#include "connected_component.h"
#include <global_variable.h>
#include <QMovie>
#include <QTimer>

StepForm::StepForm(SessionForm *parent, Log *log) :
    QWidget(parent),
    ui(new Ui::StepForm)
{
    session_ = parent;
    frame_ = parent->getFrame();
    ui->setupUi(this);

    log_ = log;
    stepCount = 0;
}

StepForm::~StepForm()
{
    delete ui;
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
    ui->feetTogetherButton->setEnabled(false);
    ui->leftFirstStepButton->setEnabled(false);
    ui->rightFirstStepButton->setEnabled(false);

    ui->loadingLabel->setMargin(0);
    ui->loadingLabel->setText("<img src=\":/icons/update-left-rotation.png\" width=\"40\"/>");

    QCoreApplication::processEvents();

    // LOG
    QString leg;
    bool correct = true, close = false;
    QTimer timer;
    //--

    if (!connectedComponent->isConnected()){
        if(connectedComponent->connect()){
            session_->setConnected();

            connectedComponent->step(code);

            timer.start();

            if(code.compare(connectedComponent->LEFTCLOSE)){
                ui->leftFirstStepButton->setEnabled(true);
                ui->rightFirstStepButton->setEnabled(true);
                leg = "LEFT";
                close = true;
            } else if(code.compare(connectedComponent->LEFTSTEP)){
                ui->feetTogetherButton->setEnabled(true);
                ui->rightFirstStepButton->setEnabled(true);
                leg = "LEFT";
            } else if(code.compare(connectedComponent->RIGHTSTEP)){
                ui->feetTogetherButton->setEnabled(true);
                ui->leftFirstStepButton->setEnabled(true);
                leg = "RIGHT";
            }

            timer.stop();

            ui->loadingLabel->setText("");
            ui->loadingLabel->setMargin(9);
        }
        else {
            connectedComponent->errorMsg("Error while calling the service");
            correct = false;
        }

        addLog(leg, correct, close, QTime());
    }
}

void StepForm::addLog(QString leg, bool correct, bool close, QTime time)
{
    if(log_ != nullptr) // sono in demo
    {
        stepCount++;
        log_->addStepEx(leg, correct, close, time);
        if(close)
            stepCount = 0;
    }
}
