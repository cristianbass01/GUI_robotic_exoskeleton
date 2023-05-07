#ifndef SELECT_USER_FORM_H
#define SELECT_USER_FORM_H

#include <QWidget>

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

private:
  Ui::SelectUserForm *ui;
};

#endif // SELECT_USER_FORM_H
