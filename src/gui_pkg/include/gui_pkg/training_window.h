#ifndef TRAINING_WINDOW_H
#define TRAINING_WINDOW_H

#include <QMainWindow>
#include <ros/ros.h>
#include <qtimer.h>
#include <std_msgs/String.h>

namespace Ui {
class TrainingWindow;
}

class TrainingWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit TrainingWindow(QWidget *parent = nullptr);
  ~TrainingWindow();

private:
  Ui::TrainingWindow *ui;

  ros::NodeHandlePtr nh_;
  ros::ServiceClient client_;
};

#endif // TRAINING_WINDOW_H
