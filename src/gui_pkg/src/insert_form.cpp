#include "insert_form.h"
#include "ui_insert_form.h"

InsertForm::InsertForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::InsertForm)
{
  ui->setupUi(this);
}

InsertForm::~InsertForm()
{
  delete ui;
}
