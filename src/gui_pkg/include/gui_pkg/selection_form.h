#ifndef SELECTION_FORM_H
#define SELECTION_FORM_H

#include <QWidget>
#include <ros/ros.h>

namespace Ui {
class SelectionForm;
}

class SelectionForm : public QWidget
{
  Q_OBJECT

public:
  explicit SelectionForm(QWidget *parent = nullptr);
  ~SelectionForm();

private:
  Ui::SelectionForm *ui;
};

#endif // SELECTION_FORM_H
