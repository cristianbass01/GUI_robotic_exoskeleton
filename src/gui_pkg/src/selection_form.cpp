#include "selection_form.h"
#include "ui_selection_form.h"

SelectionForm::SelectionForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SelectionForm)
{
  ui->setupUi(this);
}

SelectionForm::~SelectionForm()
{
  delete ui;
}
