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
  explicit SelectUserForm(QWidget *parent = nullptr);
  ~SelectUserForm();

signals:
    void on_BT_select_clicked();

private slots:
    void on_CB_selectUser_currentIndexChanged(const QString &arg1);

private:
  Ui::SelectUserForm *ui;
  //QString path = "../../Exoskeleton/Users/";
  //QList<QString> users_list;
};

#endif // SELECT_USER_FORM_H
