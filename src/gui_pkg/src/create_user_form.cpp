#include "create_user_form.h"
#include "ui_create_user_form.h"

CreateUserForm::CreateUserForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CreateUserForm)
{
  ui->setupUi(this);
}

CreateUserForm::~CreateUserForm()
{
  delete ui;
}
