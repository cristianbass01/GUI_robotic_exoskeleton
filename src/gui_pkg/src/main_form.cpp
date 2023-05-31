#include "main_form.h"
#include "ui_main_form.h"
#include "select_user_form.h"

#include "frame_window.h"
#include "training_form.h"
#include "global_variable.h"

MainForm::MainForm(FrameWindow *parent) :
  QWidget(parent),
  ui(new Ui::MainForm)
{
  frame_ = parent;
  ui->setupUi(this);
}
MainForm::~MainForm()
{
   delete ui;
}

void MainForm::on_BT_createUser_clicked()
{
    //CreateUserForm *CreateUserF = new CreateUserForm();

    //CreateUserF->show();


    frame_->customizeWindow(new SelectUserForm(frame_, true));
    frame_->show();

    this->close();
    //this->deleteLater();
}

void MainForm::on_BT_selectUser_clicked()
{
    //SelectUserForm *SelectUserF = new SelectUserForm();
    frame_->customizeWindow(new SelectUserForm(frame_));
    frame_->show();
    //SelectUserF->show();

    this->close();
    //this->deleteLater();
}

void MainForm::on_BT_demo_clicked()
{
    frame_->customizeWindow(new TrainingForm(frame_));
    frame_->show();

    this->close();
}

void MainForm::on_finishButton_clicked()
{
    frame_->close();
}
