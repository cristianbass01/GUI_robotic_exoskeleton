#include "main_form.h"
#include "ui_main_form.h"
#include "select_user_form.h"

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
    SelectUserForm SelectUserF;
    SelectUserF.show();
}

void MainForm::on_BT_selectUser_clicked()
{

}

void MainForm::on_BT_demo_clicked()
{

}
