#include "walking_form.h"
#include "ui_walking_form.h"


WalkingForm::WalkingForm(SessionForm *parent, Log *log) :
    QWidget(parent),
    ui(new Ui::WalkingForm)
{
    session_ = parent;
    frame_ = parent->getFrame();
    ui->setupUi(this);

    log_ = log;
}

WalkingForm::~WalkingForm()
{
    delete ui;
}





void WalkingForm::addLog(int set, int executed, int pause, QTime time){
    if(log_ != nullptr) // sono in demo
    {
        log_->addWalkingEx(set, executed, pause, time);
    }
}
