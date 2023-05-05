#ifndef INSERT_FORM_H
#define INSERT_FORM_H

#include <QWidget>

namespace Ui {
class InsertForm;
}

class InsertForm : public QWidget
{
  Q_OBJECT

public:
  explicit InsertForm(QWidget *parent = nullptr);
  ~InsertForm();

private:
  Ui::InsertForm *ui;
};

#endif // INSERT_FORM_H
