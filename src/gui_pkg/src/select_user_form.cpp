#include "select_user_form.h"
#include "ui_select_user_form.h"

SelectUserForm::SelectUserForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SelectUserForm)
{
  ui->setupUi(this);
}

SelectUserForm::~SelectUserForm()
{
  delete ui;
}
