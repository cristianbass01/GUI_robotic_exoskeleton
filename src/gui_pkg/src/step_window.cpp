#include "training_window.h"
#include "ui_training_window.h"
#include "step_window.h"
#include "ui_step_window.h"
#include "walking_window.h"
#include "ui_walking_window.h"
#include "control_window.h"
#include "ui_control_window.h"

StepWindow::StepWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StepWindow)
{
    ui->setupUi(this);
}

StepWindow::~StepWindow()
{
    delete ui;
}

void StepWindow::on_controlWindowButton_clicked()
{
    ControlWindow *Control = new ControlWindow();
    Control->show();

    this->hide();
}

void StepWindow::on_returnButton_clicked()
{
    TrainingWindow *Training = new TrainingWindow();
    Training->show();

    this->hide();
}

void StepWindow::on_walkingWindowButton_clicked()
{
    WalkingWindow *Walking = new WalkingWindow();
    Walking->show();

    this->hide();
}

void StepWindow::on_leftFirstStepButton_clicked()
{

}
