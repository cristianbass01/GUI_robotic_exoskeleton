#include "log_view.h"
#include "ui_log_view.h"

LogView::LogView(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LogView)
{
  ui->setupUi(this);
}

LogView::~LogView()
{
  delete ui;
}
