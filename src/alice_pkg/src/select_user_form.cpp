#include "select_user_form.h"
#include "ui_select_user_form.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QMessageBox>
#include <QStandardPaths>

#include <user_list.h>
#include <global_variable.h>
#include <log_view.h>
#include <training_form.h>

/**
 * @brief inizializza la form
 * @param parent
 * @param create True se sono in modalità creazione per l'utente
 * @param id seleziona l'utente passato
 */
SelectUserForm::SelectUserForm(FrameWindow *parent, bool create, QString id) : QWidget(parent), ui(new Ui::SelectUserForm)
{
    frame_ = parent;
    ui->setupUi(this);
    editMode(false);
    createComboBox(!create, id);
}

SelectUserForm::~SelectUserForm()
{
    delete ui;
}

/**
 * @brief Si occupa del popolamento della comboBox
 * @param start elemento da selezionare, ma se è presente un id valido allora viene selezionato quello
 * @param id imposta nella comboBox l'utente passato, se trovato
 */
void SelectUserForm::createComboBox(int start, QString id){
    // svuoto il contenuto attuale
    ui->CB_selectUser->clear();
    users.clear();

    // controllo se c'è quel numero di elementi
    start = (userList.size()>0) * start; // e' > 1 se c'è almeno un elemento nella lista, altrimenti è 0

    ui->CB_selectUser->addItem(QString("- - - Create User - - -"));

    User* u;
    // popolamento della lista formata dalla coppia (cognome+nome) e indice del file xml
    // l'indice di userList
    for(int i = 0; i<userList.size(); i++) {
      u = userList.getAt(i);
      users.append(QPair<QString, int>(u->getSurname() + " " + u->getName(), i)); // i è la posizione nel userList
    }

    // ordinamento degli elementi, non esiste un metodo diretto
    auto pairStringComparator = [](const QPair<QString, int>& pair1, const QPair<QString, int>& pair2) {
        return pair1.first < pair2.first;
    };
    qSort(users.begin(), users.end(), pairStringComparator);


    // popolamento della comboBox e ricerca del utente
    int p = 1;
    for(const auto& user : users) {
        ui->CB_selectUser->addItem(user.first);
        if(!QString::compare(userList.getAt(user.second)->getId(),id))
          start = p;
        p++;
    }

    ui->CB_selectUser->setCurrentIndex(start); // imposta il valore della comboBox
}


void SelectUserForm::setEditMode()
{
    setReadOnly(false);
    editMode(true);
}

/**
 * @brief Controlla che i dati inseriti rispettino dei canoni
 * @param edit true se sto modificando l'utente
 * @return
 */
int SelectUserForm::checkCorrect(bool edit){
  bool create = true;

  id_user = ui->TB_id->text();

  // la lunghezza minima del nome è cognome deve essere di 3 caratteri
  if(ui->TB_name->text().size() < 3 || ui->TB_surname->text().size() < 3)
  {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Warning");
    msgBox.setText("One or more fields may be incomplete");
    msgBox.setInformativeText("First name and Last name must have at least 3 letters");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
    return -1;
    }

    if(!edit && userList.findPos(id_user)>=0) // utente già presente
    {
      if(ui->TB_id->isReadOnly()) // sto modificando
          create = popUpMsg("You will overwrite a user", "Are you sure?");
      else
          create = popUpMsg("The user already exists", "Do you want overwrite?");

      return create ? 1 : -1; // -1 -> no save, 1 overwrite
    }
    return 0; // save
}

/**
 * @brief Crea l'utente
 * @param overwrite obbliga la sovrascrizione
 */
void SelectUserForm::createUser(bool overwrite){

    // trasformo il radiobutton in una string
    QString sex;
    if(ui->RB_male->isChecked())
      sex="Male";
    else if(ui->RB_female->isChecked())
      sex="Female";
    else
      sex="Other";

    QString dir;
    if(!overwrite){
        // calcolo id del utente
        dir = "a000";
        User *tmp = userList.getLast();
        if(tmp != nullptr)
        {
          QString lastDir = userList.getLast()->getDir();
          QChar chr = lastDir[0];
          int ch = chr.unicode();
          int num = lastDir.mid(1,3).toInt();
          num++;
          if(num == 1000)
          {
            num = 0;
            chr = QChar(++ch);
          }
          QString n = QString::number(num);
          dir = chr + n.rightJustified(3, '0', true);
        }
    }
    else {
      // trovo l'utente da modificare
      dir = userList.find(ui->TB_id->text())->getDir();
    }
    id_user = dir;
    User u(dir,id_user,ui->TB_name->text(),ui->TB_surname->text(),ui->DE_birthday->date(), sex,
           ui->NB_height->value(), ui->NB_weight->value(), ui->NB_upperLeg->value(), ui->NB_lowerLeg->value());

    userList.add(u);

    //creo la cartella
    QDir direct;
    if (!direct.exists(path+dir))
        direct.mkpath(path+dir);

    userList.saveXml(path + "users.xml");

    createComboBox(0,id_user);
}

/**
 * @brief Cambia lo stato tra modalità solo lettura e modalità di modifica, sono interessati gli elementi adibiti al inserimento dei dati
 * @param status True se si vole impostare in modalitè solo lettura, False per disattivarla
 */
void SelectUserForm::setReadOnly(bool status)
{
    ui->TB_name->setReadOnly(status);
    ui->TB_surname->setReadOnly(status);
    ui->DE_birthday->setReadOnly(status);
    ui->RB_male->setEnabled(!status);
    ui->RB_female->setEnabled(!status);
    ui->RB_other->setEnabled(!status);
    ui->NB_height->setReadOnly(status);
    ui->NB_weight->setReadOnly(status);
    ui->NB_upperLeg->setReadOnly(status);
    ui->NB_lowerLeg->setReadOnly(status);
}

/**
 * @brief Cambia la grafica in base la modalità
 * @param edit true se sto modificando l'utente
 */
void SelectUserForm::editMode(bool edit)
{
    int size = 40;
    ui->BT_save->setMaximumHeight(size * edit); // true -> 1, false -> 0
    ui->BT_cancel->setMaximumHeight(size * edit);
    ui->BT_create->setMaximumHeight(size * !edit);

    ui->BT_save->setMinimumHeight(size * edit);
    ui->BT_cancel->setMinimumHeight(size * edit);
    ui->BT_create->setMinimumHeight(size * !edit);

    ui->BT_delete->setVisible(!edit);
    ui->BT_select->setVisible(!edit);
    ui->BT_viewLog->setVisible(!edit);
}

/**
 * @brief Mostra un PopUp
 * @param text testo da mostrare
 * @param InformativeText informazioni aggiuntive
 * @return
 */
bool SelectUserForm::popUpMsg(QString text, QString InformativeText){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Warning");
    msgBox.setText(text);
    msgBox.setInformativeText(InformativeText);
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();
    msgBox.close();
    return (ret == QMessageBox::Yes);
}

/**
 * @brief Esegue l'aggiunta del utente o la sua modifica a seconda se si è in Create o in Edit (Select)
 */
void SelectUserForm::on_BT_create_clicked()
{
    if(ui->BT_create->text()=="Edit"){ // sono in edit mode
        setEditMode();
    }
    else { // altrimenti sto creando un utente
      int status = checkCorrect(false);
      if (status < 0)
          return;
      createUser(status);
    }
}

/**
 * @brief Recupera l'utente e avvia il @link(TrainingForm)
 */
void SelectUserForm::on_BT_select_clicked()
{
    currentUser = userList.getAt(selectUser); // imposto l'utente corrente
    frame_->customizeWindow(new TrainingForm(frame_));
    frame_->show();
}

/**
 * @brief Visualizza LogView passando l'utente selezionato
 */
void SelectUserForm::on_BT_viewLog_clicked()
{
    currentUser = userList.getAt(selectUser); // imposto l'utente corrente
    frame_->customizeWindow(new LogView(frame_, ui->TB_id->text()));
    frame_->show();
}

/**
 * @brief chiamata quando cambia l'elemento selezionato, si occupa di impostare i parametri
 * del utente selezionato al inteno dei vari cambi
 * @param index indice del elemento selezionato
 */
void SelectUserForm::on_CB_selectUser_currentIndexChanged(int index)
{
    setReadOnly(index>0); // se è maggiore di zero allora sono in selezione
    ui->BT_select->setVisible(index>0);
    ui->BT_viewLog->setVisible(index>0);
    ui->BT_delete->setVisible(index>0);

    User* u = new User;

    if(index>0) // modifiche grafiche in base alla modalità
    {
        selectUser = users[index-1].second; // recupero l'indice della del elemento
        u = userList.getAt(selectUser); // recupero l'utente

        ui->BT_create->setText("Edit");
        ui->TB_id->setMaximumWidth(610);
    }
    else {
        ui->BT_create->setText("Save");

        ui->TB_id->setMaximumWidth(0);// modifico la largezza di id,
        // in questo modo è invisibile ma occupa comunque lo spazio verticale
    }

    if(u == nullptr) { // se l'utente non è presente do errore
      QMessageBox::warning(this,"Warning", "The selected user is not present.");
      return;
    }

    // imbosto i campi in base al utente
    ui->TB_name->setText(u->getName());
    ui->TB_surname->setText(u->getSurname());
    ui->TB_id->setText(u->getId());
    ui->DE_birthday->setDate(u->getBirthday());
    switch (u->getSex().toStdString()[0]) {
        case 'M':
            ui->RB_male->setChecked(true);
            break;
        case 'F':
            ui->RB_female->setChecked(true);
            break;
        default:
            ui->RB_other->setChecked(true);
            break;
    }
    ui->NB_height->setValue(u->getHeight());
    ui->NB_weight->setValue(u->getWeight());
    ui->NB_upperLeg->setValue(u->getUpperLeg());
    ui->NB_lowerLeg->setValue(u->getLowerLeg());
}

void SelectUserForm::on_BT_save_clicked()
{
    if(checkCorrect(true) >= 0)
    {
        createUser(true);
        editMode(false);
    }
}

void SelectUserForm::on_BT_cancel_clicked()
{
    editMode(false);
    setReadOnly(true);
}

void SelectUserForm::on_BT_delete_clicked()
{
    if(popUpMsg("The current user will be deleted", "All their information and log will be deleted.\nAre you sure?"))
    {
      QDir directory(path + userList.find(ui->TB_id->text())->getDir());

      if (directory.exists()) {
          if (!directory.removeRecursively()) {

            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Error");
            msgBox.setText("Unable to delete user");
            msgBox.setInformativeText("Error deleting directory");
            msgBox.setStandardButtons(QMessageBox::Ok);
          }
      }

      // rimuovo l'utente e aggiorno l'xml
      userList.remove(ui->TB_id->text());
      userList.saveXml(path + "users.xml");
      createComboBox(1, ""); // ricarico la ComboBox
    }
}

void SelectUserForm::on_finishButton_clicked() {
  frame_->close();
}
