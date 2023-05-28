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
  frame_.reset(parent);
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

  std::shared_ptr<User> u;
  for(int i = 0; i<userList.size(); i++) {
    u = std::make_shared<User>(*userList.getAt(i));
    users.append(QPair<QString, int>(u->getSurname() + " " + u->getName(), i)); // i è la posizione nel xml
  }

  auto pairStringComparator = [](const QPair<QString, int>& pair1, const QPair<QString, int>& pair2) {
      return pair1.first < pair2.first;
  };

  // usa il metodo qSort per ordinare la lista in base al comparatore personalizzato
  qSort(users.begin(), users.end(), pairStringComparator);

  int p = 0, start = 0;
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
  user = std::make_shared<User>(*(userList.getAt(users[index].second));

  ui->TB_name->setText(user->getName());
  ui->TB_surname->setText(user->getSurname());
  ui->TB_id->setText(user->getId());

  QDir logsDir(path + user->getDir());
  QStringList logFiles = logsDir.entryList(QDir::Files);

  QTreeWidgetItem* controlItem = new QTreeWidgetItem(QStringList() << "Control Ex");
  QTreeWidgetItem* stepItem = new QTreeWidgetItem(QStringList() << "Step Ex");
  QTreeWidgetItem* walkingItem = new QTreeWidgetItem(QStringList() << "Walking Ex");

  ui->treeW_log->addTopLevelItem(controlItem);
  ui->treeW_log->addTopLevelItem(stepItem);
  ui->treeW_log->addTopLevelItem(walkingItem);

  foreach (QString logFile, logFiles) {
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << logFile);
    item->setText(0, logFile.mid(0,logFile.length() - 4)); // tolgo .log
    QDate date = QDate::fromString(logFile.mid(3, 8),"yyyyMMdd");
    item->setText(1, date.toString("dd/MM/yyyy"));  // mostro la data
    if (logFile.endsWith("ControlEx.log"))
            controlItem->addChild(item);
    else if (logFile.endsWith("StepEx.log"))
        stepItem->addChild(item);
    else if (logFile.endsWith("WalkingEx.log"))
        walkingItem->addChild(item);
    // per evitarte altri log l'ultimo caso non è un else
  }
  //ui->treeW_log->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
  //ui->treeW_log->setHorizontalScrollBarPolicy(ScrollBarAlwaysOff)
  //ui ->treeW_log->header()->setSectionResizeMode(QHeaderView::Stretch);
  //ui ->treeW_log->setVerticalScrollBar(QScrollBar::Disabled(true))

  ui->treeW_log->header()->setSectionResizeMode(QHeaderView::Stretch);

  ui->treeW_log->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  controlItem->sortChildren(0, Qt::DescendingOrder);
  stepItem->sortChildren(0, Qt::DescendingOrder);
  walkingItem->sortChildren(0, Qt::DescendingOrder);
}

void LogView::on_treeW_log_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->TableW_log->setRowCount(0);
    ui->TableW_log->setColumnCount(0);
    ui->TableW_log->clear();

    int logType;
    QString parentText;
    if (item->parent() == nullptr)
        parentText = item->text(0);
    else
        parentText = item->parent()->text(0);

    if (parentText.compare("Control Ex") == 0)
        logType = 0;
    else if (parentText.compare("Step Ex") == 0)
        logType = 1;
    else
        logType = 2;

    QFile file(path + user->getDir() + "/" + item->text(0) + ".log");

    for(int j =0; j< columnName[logType].size(); j++)
    {
        ui ->TableW_log->insertColumn(j);

        QTableWidgetItem* headerItem = new QTableWidgetItem(columnName[logType][j]);
        ui->TableW_log->setHorizontalHeaderItem(j, headerItem);
    }
    ui ->TableW_log->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


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
            QString item;
            for(int j = 0; j < log_line.size(); j++){
              item = log_line.at(j);

              if(logType < 2 && j > 0){
                if(item == "0")
                    item = "False";
                else if(item== "1")
                    item = "True";
              }
              ui->TableW_log->setItem(i, j, new QTableWidgetItem(item));
            }
            i++;

        }

        // Chiude il file dopo aver finito di leggere
        file.close();
    } else {
        // Se non è possibile aprire il file, gestisci l'errore
        //qDebug() << "Impossibile aprire il file" << fileName;
    }
}

void LogView::on_finishButton_clicked()
{
    frame_->close();
}
