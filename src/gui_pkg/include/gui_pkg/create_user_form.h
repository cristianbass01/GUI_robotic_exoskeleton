#ifndef CREATE_USER_FORM_H
#define CREATE_USER_FORM_H

#include <QWidget>

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

private:
  Ui::CreateUserForm *ui;
};

#endif // CREATE_USER_FORM_H
