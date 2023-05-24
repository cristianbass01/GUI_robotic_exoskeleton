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

    ui->loadingLabel->show();
    QMovie* loading_gif = new QMovie(":/gif/loading.gif");
    ui->loadingLabel->setMovie(loading_gif);
    loading_gif->start();
    std::cout<<loading_gif->state();

    QCoreApplication::processEvents();

    if (!connectedComponent->isConnected())
        connectedComponent->connect();
    connectedComponent->step(connectedComponent->LEFTSTEP);

    ui->feetTogetherButton->setEnabled(true);
    ui->leftFirstStepButton->setEnabled(false);
    ui->rightFirstStepButton->setEnabled(true);

    ui->loadingLabel->hide();
}

void StepForm::on_rightFirstStepButton_clicked()
{
    ui->feetTogetherButton->setEnabled(false);
    ui->leftFirstStepButton->setEnabled(false);
    ui->rightFirstStepButton->setEnabled(false);
    QCoreApplication::processEvents();

    if (!connectedComponent->isConnected())
        connectedComponent->connect();
    connectedComponent->step(connectedComponent->RIGHTSTEP);

    ui->feetTogetherButton->setEnabled(true);
    ui->leftFirstStepButton->setEnabled(true);
    ui->rightFirstStepButton->setEnabled(false);
}

void StepForm::on_feetTogetherButton_clicked()
{
    ui->feetTogetherButton->setEnabled(false);
    ui->leftFirstStepButton->setEnabled(false);
    ui->rightFirstStepButton->setEnabled(false);
    QCoreApplication::processEvents();

    if (!connectedComponent->isConnected())
        connectedComponent->connect();
    connectedComponent->step(connectedComponent->PAIR);

    ui->feetTogetherButton->setEnabled(false);
    ui->leftFirstStepButton->setEnabled(true);
    ui->rightFirstStepButton->setEnabled(true);
}
