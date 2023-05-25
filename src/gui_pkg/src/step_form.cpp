#include "step_form.h"
#include "ui_step_form.h"

#include "session_form.h"

#include "connected_component.h"
#include <global_variable.h>
#include <QMovie>

StepForm::StepForm(SessionForm *parent) :
    QWidget(parent),
    ui(new Ui::StepForm)
{
    session_ = parent;
    frame_ = parent->getFrame();
    ui->setupUi(this);
}

StepForm::~StepForm()
{
    delete ui;
}

void StepForm::on_leftFirstStepButton_clicked()
{
    ui->feetTogetherButton->setEnabled(false);
    ui->leftFirstStepButton->setEnabled(false);
    ui->rightFirstStepButton->setEnabled(false);

    ui->loadingLabel->setMargin(0);
    ui->loadingLabel->setText("<img src=\":/icons/update-left-rotation.png\" width=\"40\"/>");
    //QMovie* loading_gif = new QMovie(":/gif/loading.gif");
    //ui->loadingLabel->setMovie(loading_gif);
    //loading_gif->start();

    QCoreApplication::processEvents();

    if (!connectedComponent->isConnected()){
        if(connectedComponent->connect())
            session_->setConnected();
    }

    connectedComponent->step(connectedComponent->LEFTSTEP);

    ui->feetTogetherButton->setEnabled(true);
    ui->leftFirstStepButton->setEnabled(false);
    ui->rightFirstStepButton->setEnabled(true);

    ui->loadingLabel->setText("");
    ui->loadingLabel->setMargin(9);
}

void StepForm::on_rightFirstStepButton_clicked()
{
    ui->feetTogetherButton->setEnabled(false);
    ui->leftFirstStepButton->setEnabled(false);
    ui->rightFirstStepButton->setEnabled(false);

    ui->loadingLabel->setMargin(0);
    ui->loadingLabel->setText("<img src=\":/icons/update-left-rotation.png\" width=\"40\"/>");
    //QMovie* loading_gif = new QMovie(":/gif/loading.gif");
    //ui->loadingLabel->setMovie(loading_gif);
    //loading_gif->start();

    QCoreApplication::processEvents();

    if (!connectedComponent->isConnected()){
        if(connectedComponent->connect())
            session_->setConnected();
    }

    connectedComponent->step(connectedComponent->RIGHTSTEP);

    ui->feetTogetherButton->setEnabled(true);
    ui->leftFirstStepButton->setEnabled(true);
    ui->rightFirstStepButton->setEnabled(false);

    ui->loadingLabel->setText("");
    ui->loadingLabel->setMargin(9);
}

void StepForm::on_feetTogetherButton_clicked()
{
    ui->feetTogetherButton->setEnabled(false);
    ui->leftFirstStepButton->setEnabled(false);
    ui->rightFirstStepButton->setEnabled(false);

    ui->loadingLabel->setMargin(0);
    ui->loadingLabel->setText("<img src=\":/icons/update-left-rotation.png\" width=\"40\"/>");
    //QMovie* loading_gif = new QMovie(":/gif/loading.gif");
    //ui->loadingLabel->setMovie(loading_gif);
    //loading_gif->start();

    QCoreApplication::processEvents();

    if (!connectedComponent->isConnected()){
        if(connectedComponent->connect()){
            session_->setConnected();

            connectedComponent->step(connectedComponent->PAIR);

            ui->feetTogetherButton->setEnabled(false);
            ui->leftFirstStepButton->setEnabled(true);
            ui->rightFirstStepButton->setEnabled(true);

            ui->loadingLabel->setText("");
            ui->loadingLabel->setMargin(11);
        }
        else {
            connectedComponent->errorMsg("Error while calling the service" );
        }
    }


}
