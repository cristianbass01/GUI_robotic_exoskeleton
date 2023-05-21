#include "training_window.h"
#include "ui_training_window.h"
#include "ros/ros.h"
#include "gui_pkg/serv.h"
#include <cstdlib>

TrainingWindow::TrainingWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::TrainingWindow)
{
  ui->setupUi(this);

  nh_.reset(new ros::NodeHandle("~"));
  client_ = nh_->serviceClient<gui_pkg::serv>("/walking");

}

TrainingWindow::~TrainingWindow()
{
  delete ui;
}
