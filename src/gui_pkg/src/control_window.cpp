#include "training_window.h"
#include "ui_training_window.h"
#include "step_window.h"
#include "ui_step_window.h"
#include "walking_window.h"
#include "ui_walking_window.h"
#include "control_window.h"
#include "ui_control_window.h"

ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);
}

ControlWindow::~ControlWindow()
{
    delete ui;
}

void ControlWindow::on_walkingWindowButton_clicked()
{
    WalkingWindow *Walking = new WalkingWindow();
    Walking->show();

    this->hide();
}

void ControlWindow::on_stepWindowButton_clicked()
{
    StepWindow *Step = new StepWindow();
    Step->show();

    this->hide();
}

void ControlWindow::on_returnButton_clicked()
{
    TrainingWindow *Training = new TrainingWindow();
    Training->show();

    this->hide();
}
