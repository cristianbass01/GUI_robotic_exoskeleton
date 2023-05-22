#include "training_window.h"
#include "ui_training_window.h"
#include "step_window.h"
#include "ui_step_window.h"
#include "walking_window.h"
#include "ui_walking_window.h"
#include "control_window.h"
#include "ui_control_window.h"

WalkingWindow::WalkingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WalkingWindow)
{
    ui->setupUi(this);

}

WalkingWindow::~WalkingWindow()
{
    delete ui;
}

void WalkingWindow::on_controlWindowButton_clicked()
{
    ControlWindow *Control = new ControlWindow();
    Control->show();

    this->hide();
}


void WalkingWindow::on_stepWindowButton_clicked()
{
    StepWindow *Step = new StepWindow();
    Step->show();

    this->hide();
}

void WalkingWindow::on_returnButton_clicked()
{
    TrainingWindow *Training = new TrainingWindow();
    Training->show();

    this->hide();
}
