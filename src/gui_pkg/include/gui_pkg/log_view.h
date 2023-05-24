#ifndef LOG_VIEW_H
#define LOG_VIEW_H

#include <QWidget>
#include <global_variable.h>
#include <user_list.h>
#include <QTreeWidgetItem>

namespace Ui {
class LogView;
}

class LogView : public QWidget
{
  Q_OBJECT
private slots:
  void createComboBox(QString id);

  void on_CB_user_currentIndexChanged(int index);

  void on_treeW_log_itemClicked(QTreeWidgetItem *item, int column);

private:
  QList<QPair<QString, int>> users;

public:
  explicit LogView(QWidget *parent = nullptr, QString id = NULL);
  ~LogView();

private:
  Ui::LogView *ui;
};

#endif // LOG_VIEW_H
