#ifndef SELECT_USER_FORM_H
#define SELECT_USER_FORM_H

#include <QWidget>
#include <QObject>
#include <QTextStream>
#include <QString>
#include <iostream>
#include <fstream>
#include <QList>
#include <ros/ros.h>
#include <global_variable.h>

namespace Ui {
class SelectUserForm;
}

class SelectUserForm : public QWidget
{
  Q_OBJECT

public:
  explicit SelectUserForm(QWidget *parent = nullptr, bool create = false);
  ~SelectUserForm();

signals:
    //void on_BT_select_clicked();

private slots:
    void setReadOnly(bool status, bool id);
    void on_BT_create_clicked();
    void on_BT_selectUser_clicked();
    void createComboBox(int start, QString id);
    void on_CB_selectUser_currentIndexChanged(int index);

public slots:
  void rejected();
  void createUser();

private:
  Ui::SelectUserForm *ui;
  QString id_user;
  QList<QPair<QString, int>> users;
};

#endif // SELECT_USER_FORM_H
