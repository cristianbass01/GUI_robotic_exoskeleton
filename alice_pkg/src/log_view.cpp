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

  delete controlItem;
  delete stepItem;
  delete walkingItem;
}

/**
 * @brief Inserisce gli elementi al interno del comboBox
 * @param id identidicativo del utente
 */
void LogView::createComboBox(QString id){
  ui->CB_user->clear();
  users.clear();

  // creo una lista formata dalla coppia QString e int, dove l'itero è la posizione del utente nella userList
  // in questo modo posso recuperare l'elemento dalla userList tramite la sua posizione e non tramite il nome e il cognome
  for(int i = 0; i<userList.size(); i++)
    users.append(QPair<QString, int>(userList.getAt(i)->getSurname() + " " + userList.getAt(i)->getName(), i));

  // metodo per confrontare stringhe per ordinare gli elementi
  auto pairStringComparator = [](const QPair<QString, int>& pair1, const QPair<QString, int>& pair2) {
      return pair1.first < pair2.first;
  };

  // usa il metodo qSort per ordinare la lista in base al comparatore personalizzato
  qSort(users.begin(), users.end(), pairStringComparator);

  int p = 0, start = 0;
  for(const auto& user : users) {
      ui->CB_user->addItem(user.first); // aggiungo l'elemento della combobox
      if(!QString::compare(userList.getAt(user.second)->getId(),id))
        start = p; // se trovo l'elemeneto passato mi salvo la posizione
      p++;
  }

  ui->CB_user->setCurrentIndex(start);
}

/**
 * @brief Richiamata quando l'elemento selezionato cambia
 * @param index indice del elemento selezionato
 */
void LogView::on_CB_user_currentIndexChanged(int index)
{
  ui->treeW_log->clear();
  user = userList.getAt(users[index].second); // recupero l'utente, index mi da la posizione della lista ordinata,
  // quindi con devo estrapolare la sua posizione in userList tramite users[index].second

  ui->TB_name->setText(user->getName());
  ui->TB_surname->setText(user->getSurname());
  ui->TB_id->setText(user->getId());

  QDir logsDir(path + user->getDir());
  QStringList logFiles = logsDir.entryList(QDir::Files);

  // aggiungo le categorie del TreeWidget
  controlItem = new QTreeWidgetItem(QStringList() << "Control exercise");
  stepItem = new QTreeWidgetItem(QStringList() << "Step exercise");
  walkingItem = new QTreeWidgetItem(QStringList() << "Walking exercise");

  ui->treeW_log->addTopLevelItem(controlItem);
  ui->treeW_log->addTopLevelItem(stepItem);
  ui->treeW_log->addTopLevelItem(walkingItem);

  // popolo la QTreeWidget
  foreach (QString logFile, logFiles) {
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << logFile);
    item->setText(0, logFile.mid(0,logFile.length() - 4)); // tolgo .log
    QDate date = QDate::fromString(logFile.mid(3, 8),"yyyyMMdd");
    item->setText(1, date.toString("dd/MM/yyyy"));  // mostro la data
    if (logFile.endsWith("ControlEx.log")) // controllo tipo di log
            controlItem->addChild(item);
    else if (logFile.endsWith("StepEx.log"))
        stepItem->addChild(item);
    else if (logFile.endsWith("WalkingEx.log"))
        walkingItem->addChild(item);
  }

  //ui->treeW_log->header()->setSectionResizeMode(QHeaderView::Stretch);
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

    // recupero che log è stato premuto e il tipo
    if (item->parent() == nullptr)
        parentText = item->text(0);
    else
        parentText = item->parent()->text(0);

    if (parentText.compare("Control exercise") == 0)
        logType = CONTROL;
    else if (parentText.compare("Step exercise") == 0)
        logType = STEP;
    else
        logType = WALKING;

    // apro il file di log
    QFile file(path + user->getDir() + "/" + item->text(0) + ".log");


    // inserisco i nomi delle colonne in base al tipo di Log
    for(int j =0; j< columnName[logType].size(); j++)
    {
        ui->TableW_log->insertColumn(j);
        ui->TableW_log->setHorizontalHeaderItem(j, new QTableWidgetItem(columnName[logType][j]));
    }
    ui ->TableW_log->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    // Apre il file in modalità di lettura
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // Legge il contenuto del file
        int i = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();

            ui->TableW_log->insertRow(i);
            QStringList log_line = line.split(";"); // splitto line per recuperare i vari campi
            QString item;
            for(int j = 0; j < log_line.size(); j++){ // gli inserisco nelle giuste colonne
              item = log_line.at(j);

              if(j > 3 && (logType == CONTROL || logType == STEP)){ // sostituisco 0 e 1 per facilitare lettura
                if(item == "0")
                    item = "False";
                else if(item== "1")
                    item = "True";
              }
              ui->TableW_log->setItem(i, j, new QTableWidgetItem(item));
            }
            i++;

        }
        file.close();
    }
}

void LogView::on_finishButton_clicked()
{
    frame_->close();
}
