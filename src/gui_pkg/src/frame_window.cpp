#include "frame_window.h"
#include "ui_frame_window.h"

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
