#include "control_form.h"
#include "ui_control_form.h"

ControlForm::ControlForm(SessionForm *parent,  Log *log) :
    QWidget(parent),
    ui(new Ui::ControlForm)
{
    session_ = parent;
    frame_ = parent->getFrame();
    log_.reset(log);
    ui->setupUi(this);
}

ControlForm::~ControlForm()
{
    delete ui;
}


void ControlForm::addLog(QString leg, bool correct, bool close, QTime time){
  if(log_ != nullptr) // sono in demo
  {

  }
}

void ControlForm::setEnabled(bool state){
    ui->stopButton->setEnabled(state);
    ui->startButton->setEnabled(state);
}
