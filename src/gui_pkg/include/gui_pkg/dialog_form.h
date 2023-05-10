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

public slots:
  void setTitle(QString title);

  void setDescription(QString desc);

signals:
  void on_BT_dialog_accepted();

  void on_BT_dialog_rejected();


private:
  Ui::DialogForm *ui;
};

#endif // DIALOG_FORM_H
