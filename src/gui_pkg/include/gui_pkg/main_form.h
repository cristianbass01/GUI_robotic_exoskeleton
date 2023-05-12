#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QWidget>
#include <ros/ros.h>
#include "select_user_form.h"
#include "create_user_form.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
  Q_OBJECT

public:
  explicit MainForm(QWidget *parent = nullptr);
  ~MainForm();

private slots:
  void on_BT_createUser_clicked();

  void on_BT_selectUser_clicked();

  void on_BT_demo_clicked();

private:
  Ui::MainForm *ui;
};

#endif // MAIN_FORM_H
