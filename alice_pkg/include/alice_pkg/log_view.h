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

  /**
   * @brief Inserisce gli elementi al interno del comboBox, e imposta quello passato
   * @param id identidicativo del utente
   */
  void createComboBox(QString id = "");

  /**
   * @brief Richiamata quando l'elemento selezionato cambia
   * @param index indice del elemento selezionato
   */
  void on_CB_user_currentIndexChanged(int index);

  void on_treeW_log_itemClicked(QTreeWidgetItem *item, int column);

  void on_finishButton_clicked();

private:
  QList<QPair<QString, int>> users; // gestione utente e la sua posizione

public:
  explicit LogView(FrameWindow *parent = nullptr, QString id = nullptr);
  ~LogView();

private:
  Ui::LogView *ui;
  FrameWindow *frame_;

  User* user;

  // nomi delle colonne
  const QVector< QVector< QString > > columnName = {
    {"#", "Timestamp", "Leg", "Correct", "Time"},           // ControlLog
    {"#", "Timestamp", "Leg", "Step Count", "Correct", "Last", "Time"}, // StepLog
    {"#", "Timestamp", "Selected", "Executed", "Pause", "Time"}  // walkingLog
  };

  const int CONTROL = 0;
  const int STEP = 1;
  const int WALKING = 2;

  QTreeWidgetItem* controlItem;
  QTreeWidgetItem* stepItem;
  QTreeWidgetItem* walkingItem;
};

#endif // LOG_VIEW_H
