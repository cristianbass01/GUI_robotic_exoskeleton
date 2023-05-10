#include "dialog_form.h"
#include "ui_dialog_form.h"

DialogForm::DialogForm(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogForm)
{
  ui->setupUi(this);
}

DialogForm::~DialogForm()
{
  delete ui;
}
