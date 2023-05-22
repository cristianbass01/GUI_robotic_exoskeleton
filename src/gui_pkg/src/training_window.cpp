#include "training_window.h"
#include "ui_training_window.h"
#include "step_window.h"
#include "ui_step_window.h"
#include "walking_window.h"
#include "ui_walking_window.h"
#include "control_window.h"
#include "ui_control_window.h"

TrainingWindow::TrainingWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::TrainingWindow)
{
  ui->setupUi(this);
}

TrainingWindow::~TrainingWindow()
{
  delete ui;
}

void TrainingWindow::on_standButton_clicked()
{

}

void TrainingWindow::on_stepButton_clicked()
{
    StepWindow *Step = new StepWindow();
    Step->show();

    this->hide();
}

void TrainingWindow::on_walkButton_clicked()
{
    WalkingWindow *Walking = new WalkingWindow();
    Walking->show();

    this->hide();
}

void TrainingWindow::on_controlButton_clicked()
{
    ControlWindow *Control = new ControlWindow();
    Control->show();

    this->hide();
}

void TrainingWindow::on_finishButton_clicked()
{

}
