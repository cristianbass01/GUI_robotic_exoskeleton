#include "control_form.h"
#include "ui_control_form.h"

ControlForm::ControlForm(SessionForm *parent) :
    QWidget(parent),
    ui(new Ui::ControlForm)
{
    session_ = parent;
    frame_ = parent->getFrame();
    ui->setupUi(this);
}

ControlForm::~ControlForm()
{
    delete ui;
}
