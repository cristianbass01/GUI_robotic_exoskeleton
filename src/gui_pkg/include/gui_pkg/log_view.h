#ifndef LOG_VIEW_H
#define LOG_VIEW_H

#include <QWidget>

namespace Ui {
class LogView;
}

class LogView : public QWidget
{
  Q_OBJECT

public:
  explicit LogView(QWidget *parent = nullptr);
  ~LogView();

private:
  Ui::LogView *ui;
};

#endif // LOG_VIEW_H
