#ifndef LOG_VIEW_H
#define LOG_VIEW_H

#include <QWidget>
#include <global_variable.h>
#include <user_list.h>
#include <QTreeWidgetItem>
#include <frame_window.h>
#include <QVector>
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

  void on_finishButton_clicked();

private:
  QList<QPair<QString, int>> users;

public:
  explicit LogView(FrameWindow *parent = nullptr, QString id = nullptr);
  ~LogView();

private:
  Ui::LogView *ui;
  std::shared_ptr<FrameWindow> frame_;

  User* user;

  const QVector< QVector< QString > > columnName = {
    {"#", "Leg", "Correct", "Time"},           // ControlLog
    {"#", "Leg", "Correct", "Closed", "Time"}, // StepLog
    {"#", "Set", "Executed", "Pause", "Time"}  // walkingLog

  };

  QTreeWidgetItem* controlItem;
  QTreeWidgetItem* stepItem;
  QTreeWidgetItem* walkingItem;

  /*
  const QString walkingLog[5] = {"#", "Set", "Executed", "Pause", "Time"};
  const QString StepLog[5] = {"#", "Leg", "Correct", "Closed", "Time"};
  const QString ControlLog[5] = {"#", "Leg", "Correct", "Time"};
  */
};

#endif // LOG_VIEW_H
