#include "frame_window.h"
#include "ui_frame_window.h"

#include "main_form.h"

#include "session_form.h"
#include "training_form.h"

FrameWindow::FrameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrameWindow)
{
    ui->setupUi(this);
}

FrameWindow::~FrameWindow()
{
    delete ui;
}

void FrameWindow::customizeWindow(QWidget *widget_to_insert){
    auto last = ui->parentLayout->takeAt(0);
    if(last){
        ui->parentLayout->removeWidget(last->widget());
        last->widget()->close();
    }
    currentForm = widget_to_insert->objectName();
    ui->parentLayout->addWidget(widget_to_insert);
}

void FrameWindow::setConnected(bool state){
    if (ui->parentLayout->takeAt(0)){
        if(currentForm.toStdString().compare("SessionForm") == 0)
            qobject_cast<SessionForm *>( ui->parentLayout->takeAt(0)->widget())->setConnected(state);
        else
            qobject_cast<TrainingForm *>( ui->parentLayout->takeAt(0)->widget())->setConnected(state);
    }
}

void FrameWindow::on_actionHome_triggered()
{
    this->customizeWindow(new MainForm(this));
}

