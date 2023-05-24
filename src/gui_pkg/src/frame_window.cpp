#include "frame_window.h"
#include "ui_frame_window.h"

#include "main_form.h"

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
    if(last != nullptr){
        ui->parentLayout->removeWidget(last->widget());
        last->widget()->close();
    }

    ui->parentLayout->addWidget(widget_to_insert);
}

void FrameWindow::on_actionHome_triggered()
{
    this->customizeWindow(new MainForm(this));
}
