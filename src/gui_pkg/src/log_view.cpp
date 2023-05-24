#include "log_view.h"
#include "ui_log_view.h"
#include <QDir>
#include <QString>
#include <QDate>
#include <QTextStream>

LogView::LogView(FrameWindow *parent, QString id) :
  QWidget(parent),
  ui(new Ui::LogView)
{
  frame_ = parent;
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

  QDir logsDir(path + u->getDir());
  QStringList logFiles = logsDir.entryList(QDir::Files);

  QTreeWidgetItem* walkingItem = new QTreeWidgetItem(QStringList() << "Walking Ex");
  QTreeWidgetItem* stepItem = new QTreeWidgetItem(QStringList() << "Step Ex");
  ui->treeW_log->addTopLevelItem(walkingItem);
  ui->treeW_log->addTopLevelItem(stepItem);

  foreach (QString logFile, logFiles) {
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << logFile);
    item->setText(0, logFile.mid(0,logFile.length() - 4)); // tolgo .log
    QDate date = QDate::fromString(logFile.mid(3, 8),"yyyyMMdd");
    item->setText(1, date.toString("dd/MM/yyyy"));  // mostro la data
    if (logFile.endsWith("WalkingEx.log"))
        walkingItem->addChild(item);
    else if (logFile.endsWith("StepEx.log"))
        stepItem->addChild(item);
  }
  //ui->treeW_log->resizeColumnToContents(0);
  //ui->treeW_log->resizeColumnToContents(1);
}

void LogView::on_treeW_log_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->TableW_log->setRowCount(0);
    ui->TableW_log->setColumnCount(0);
    ui->TableW_log->clear();

        QFile file(path + userList.getAt(users[column].second)->getDir() + "/" + item->text(0) + ".log");
    for(int j =0; j< 5; j++)
        ui ->TableW_log->insertColumn(j);

    // Apre il file in modalità di lettura
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Crea un oggetto QTextStream per leggere il file
        QTextStream in(&file);

        // Legge il contenuto del file riga per riga
        int i = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            // Fai qualcosa con la riga letta, ad esempio stampala
            // qDebug() << line;
            ui->TableW_log->insertRow(i);
            QStringList log_line = line.split(";");
            for(int j = 0; j < log_line.size(); j++)
              ui->TableW_log->setItem(i, j, new QTableWidgetItem(log_line.at(j)));
            i++;

        }

        // Chiude il file dopo aver finito di leggere
        file.close();
    } else {
        // Se non è possibile aprire il file, gestisci l'errore
        //qDebug() << "Impossibile aprire il file" << fileName;
    }
}
