#include "main_form.h"
#include "ui_main_form.h"
#include "select_user_form.h"
#include "create_user_form.h"
#include "training_window.h"

MainForm::MainForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MainForm)
{
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


  SelectUserForm *SelectUserF = new SelectUserForm(nullptr, true);
  SelectUserF->show();
  this->hide();
  //this->deleteLater();
}

void MainForm::on_BT_selectUser_clicked()
{
  SelectUserForm *SelectUserF = new SelectUserForm();
  SelectUserF->show();

  this->hide();
  //this->deleteLater();
}

void MainForm::on_BT_demo_clicked()
{
    TrainingWindow *Training = new TrainingWindow();
    Training->show();

    this->hide();
}
