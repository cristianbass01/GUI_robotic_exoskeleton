#include "walking_form.h"
#include "ui_walking_form.h"

WalkingForm::WalkingForm(SessionForm *parent) :
    QWidget(parent),
    ui(new Ui::WalkingForm)
{
    session_ = parent;
    frame_ = parent->getFrame();
    ui->setupUi(this);
}

WalkingForm::~WalkingForm()
{
    delete ui;
}
