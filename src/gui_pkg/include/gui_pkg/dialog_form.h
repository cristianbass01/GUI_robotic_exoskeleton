#ifndef DIALOG_FORM_H
#define DIALOG_FORM_H

#include <QDialog>

namespace Ui {
class DialogForm;
}

class DialogForm : public QDialog
{
  Q_OBJECT

public:
  explicit DialogForm(QWidget *parent = nullptr);
  ~DialogForm();

private:
  Ui::DialogForm *ui;
};

#endif // DIALOG_FORM_H
