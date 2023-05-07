#ifndef CREATE_USER_FORM_H
#define CREATE_USER_FORM_H

#include <QWidget>
#include <iostream>
#include <fstream>

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
  void test_Dialog();

private:
  Ui::CreateUserForm *ui;
};

#endif // CREATE_USER_FORM_H
