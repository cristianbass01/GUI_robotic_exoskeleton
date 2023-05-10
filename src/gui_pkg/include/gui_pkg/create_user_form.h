#ifndef CREATE_USER_FORM_H
#define CREATE_USER_FORM_H

#include <QWidget>
#include <QObject>
#include <QTextStream>
#include <QString>
#include <iostream>
#include <fstream>
#include <QList>
#include <QCloseEvent>
#include <QStandardPaths>
#include <ros/ros.h>

namespace Ui {
class CreateUserForm;
}

class CreateUserForm : public QWidget
{
  Q_OBJECT

public:
  explicit CreateUserForm(QWidget *parent = nullptr);
  ~CreateUserForm();

private slots:
  void on_BT_create_clicked();
  void closeEvent (QCloseEvent *event);

  void on_BT_selectUser_clicked();

public slots:
  void rejected();
  void createUser();

private:
  Ui::CreateUserForm *ui;


  QString path = QStandardPaths::HomeLocation + "/Alice/Log/";
  QString cf;
  QList<QString> users_list;

  //QString path(QStandardPaths::locate(QStandardPaths::DesktopLocation, "") "/");
};

#endif // CREATE_USER_FORM_H
