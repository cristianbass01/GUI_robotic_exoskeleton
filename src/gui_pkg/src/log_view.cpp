#include "log_view.h"
#include "ui_log_view.h"
#include <QDir>

LogView::LogView(QWidget *parent, QString id) :
  QWidget(parent),
  ui(new Ui::LogView)
{
  ui->setupUi(this);
  createComboBox(id);
}

LogView::~LogView()
{
  delete ui;
}

void LogView::createComboBox(QString id){
  ui->CB_user->clear();
  users.clear();

  User* u;
  for(int i = 0; i<userList.size(); i++) {
    u = userList.getAt(i);
    users.append(QPair<QString, int>(u->getSurname() + " " + u->getName(), i)); // i è la posizione nel xml
  }

  auto pairStringComparator = [](const QPair<QString, int>& pair1, const QPair<QString, int>& pair2) {
      return pair1.first < pair2.first;
  };

  // usa il metodo qSort per ordinare la lista in base al comparatore personalizzato
  qSort(users.begin(), users.end(), pairStringComparator);

  int p = 0, start;
  for(const auto& user : users) {
      ui->CB_user->addItem(user.first);
      if(!QString::compare(userList.getAt(user.second)->getId(),id))
        start = p;
      p++;
  }

  //ui->CB_selectUser->addItems(users);

  ui->CB_user->setCurrentIndex(start);
}

void LogView::on_CB_user_currentIndexChanged(int index)
{
  ui->treeW_log->clear();
  User* u = userList.getAt(index);

  ui->TB_name->setText(u->getName());
  ui->TB_surname->setText(u->getSurname());
  ui->TB_id->setText(u->getId());

  QDir logsDir(u->getDir());
  QStringList logFiles = logsDir.entryList(QDir::Files);

  QTreeWidgetItem* walkingItem = new QTreeWidgetItem(QStringList() << "Walking Ex");
  QTreeWidgetItem* stepItem = new QTreeWidgetItem(QStringList() << "Step Ex");
  ui->treeW_log->addTopLevelItem(walkingItem);
  ui->treeW_log->addTopLevelItem(stepItem);

  foreach (QString logFile, logFiles) {
      if (logFile.endsWith("WalkingEx.log")) {
          QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << logFile);
          walkingItem->addChild(item);
      } else if (logFile.startsWith("StepEx.log")) {
          QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << logFile);
          stepItem->addChild(item);
      }
  }

}
