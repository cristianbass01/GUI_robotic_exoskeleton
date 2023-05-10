#ifndef CREATE_USER_FORM_H
#define CREATE_USER_FORM_H

#include <QWidget>
#include <QObject>
#include <QTextStream>
#include <QString>
#include <iostream>
#include <fstream>
#include <list>

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

  void on_BT_test_clicked();

public slots:
  void rejected();
  void createUser(std::list<QString> users_list, QString cf);

private:
  Ui::CreateUserForm *ui;
  QString path = "../../Exoskeleton/Users/";

  //QString path(QStandardPaths::locate(QStandardPaths::DesktopLocation, "") "/");
};

#endif // CREATE_USER_FORM_H
