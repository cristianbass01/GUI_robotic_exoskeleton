#include "step_form.h"
#include "ui_step_form.h"

#include "session_form.h"

#include "connected_component.h"
#include <global_variable.h>
#include <QMovie>
#include <QTimer>
#include <QElapsedTimer>
#include <QMessageBox>

StepForm::StepForm(SessionForm *parent, Log *log) :
    QWidget(parent),
    ui(new Ui::StepForm)
{
    session_ = parent;
    frame_ = parent->getFrame();
    ui->setupUi(this);

    this->setEnabled(true);
    log_ = log;
    stepCount = 0;
}

StepForm::~StepForm()
{
    delete ui;
    delete log_;
}

void StepForm::on_leftFirstStepButton_clicked()
{
    frame_->showStatus("Moving: left step...");
    this->movement(ConnectedComponent::getInstance().LEFTSTEP);
    frame_->clearStatus();
}

void StepForm::on_rightFirstStepButton_clicked()
{
    frame_->showStatus("Moving: right step...");
    this->movement(ConnectedComponent::getInstance().RIGHTSTEP);
    frame_->clearStatus();
}

void StepForm::on_feetTogetherButton_clicked()
{
    frame_->showStatus("Moving: closing step...");
    this->movement(ConnectedComponent::getInstance().LEFTCLOSE);
    frame_->clearStatus();
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

    if (!ConnectedComponent::getInstance().isConnected())
        session_->on_connectButton_clicked();

    QApplication::processEvents();

    if (ConnectedComponent::getInstance().isConnected()){
        try {
            QElapsedTimer timer;
            timer.start();

            if(!ConnectedComponent::getInstance().step(code)){
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Warning");
                msgBox.setText("Movement failed");
                msgBox.setInformativeText("Exoskeleton failed the step");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.exec();
                correct = false;
            }

            this->setEnabled(true);
            session_->setEnabled(true);
            session_->updateImage();

            ui->loadingLabel->setText("");
            ui->loadingLabel->setMargin(9);

            ms = static_cast<int>(timer.elapsed());
        } catch (...) {
            ConnectedComponent::getInstance().errorConnectionMsg("Error while calling the service");
            correct = false;
        }

    }
    else {
        ConnectedComponent::getInstance().errorConnectionMsg("Error during the connection to the service");
        session_->setConnected(false);
        correct = false;
        this->setEnabled(true);
        session_->setEnabled(true);
    }

    if(code.compare(ConnectedComponent::getInstance().LEFTCLOSE) == 0){
        leg = "LEFT";
        close = true;
    } else if(code.compare(ConnectedComponent::getInstance().LEFTSTEP)== 0){
        leg = "LEFT";
    } else if(code.compare(ConnectedComponent::getInstance().RIGHTSTEP)== 0){
        leg = "RIGHT";
    }

    addLog(leg, correct, close, t.addMSecs(ms));
}

/**
 * @brief Aggiunge Log per l'azione Step
 * @param leg Gamba con cui è stata eseguito il movimento
 * @param correct Se il passo si è concluso correttamente
 * @param close Se il passo è di chiusura
 * @param time Tempo di esecuzione
 */
void StepForm::addLog(QString leg, bool correct, bool close, QTime time)
{
    if(log_ != nullptr) // non sono in demo
    {
        log_->addStepEx(leg, ++stepCount, correct, close, time);
        if(close) // se è l'ultimo passo allora azzero il numero di passi
            stepCount = 0;
    }
}

void StepForm::setEnabled(bool state){
    if (!state){
        ui->feetTogetherButton->setEnabled(false);
        ui->leftFirstStepButton->setEnabled(false);
        ui->rightFirstStepButton->setEnabled(false);
    }
    else {
        std::string lastStep = ConnectedComponent::getInstance().getCurrentState();

        ui->feetTogetherButton->setEnabled(false);
        ui->leftFirstStepButton->setEnabled(false);
        ui->rightFirstStepButton->setEnabled(false);

        if(lastStep.compare(ConnectedComponent::getInstance().LEFTSTEP) == 0){
            ui->rightFirstStepButton->setEnabled(true);
        } else if(lastStep.compare(ConnectedComponent::getInstance().RIGHTSTEP) == 0){
            ui->feetTogetherButton->setEnabled(true);
            ui->leftFirstStepButton->setEnabled(true);
        } else{
            ui->leftFirstStepButton->setEnabled(true);
            ui->rightFirstStepButton->setEnabled(true);
        }
    }
}
