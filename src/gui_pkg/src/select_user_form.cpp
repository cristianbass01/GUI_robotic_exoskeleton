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

SelectUserForm::SelectUserForm(FrameWindow *parent, bool create, QString id) :
  QWidget(parent), ui(new Ui::SelectUserForm)
{
    frame_ = parent;
    ui->setupUi(this);
    createComboBox(!create, id);
    editMode(false);
}

SelectUserForm::~SelectUserForm()
{
    delete ui;
}

void SelectUserForm::createComboBox(int start, QString id){
    ui->CB_selectUser->clear();
    users.clear();

    ui->CB_selectUser->addItem(QString("- - - Create User - - -"));

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

    int p = 1;
    for(const auto& user : users) {
        ui->CB_selectUser->addItem(user.first);
        if(!QString::compare(userList.getAt(user.second)->getId(),id))
          start = p;
        p++;
    }

    //ui->CB_selectUser->addItems(users);

    ui->CB_selectUser->setCurrentIndex(start);
}


void SelectUserForm::on_CB_selectUser_currentIndexChanged(int index)
{
    setReadOnly(ui->CB_selectUser->currentIndex()!=0, ui->CB_selectUser->currentIndex()!=0);
    ui->BT_selectUser->setVisible(ui->CB_selectUser->currentIndex()>0);
    ui->BT_viewLog->setVisible(ui->CB_selectUser->currentIndex()>0);

    User* u = new User;

    if(index>0)
    {
        selectUser = users[index-1].second;
        u = userList.getAt(selectUser);
        ui->BT_create->setText("Edit");

    }
    else {
        ui->BT_create->setText("Save");
    }

    if(u == nullptr) {
      QMessageBox::warning(this,"Warning", "The selected user is not present.");
      return; //// come proseguo? elimino dal file, o chiedo di recrearlo?
    }
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

void SelectUserForm::on_BT_create_clicked()
{
    if(ui->BT_create->text()=="Edit"){
        setReadOnly(false, true);
        editMode(true);
        //ui->BT_create->setText("Save");
    }
    else {
      int status = checkCorrect(false);
      if (status < 0)
          return;
      createUser(status);
    }
}

int SelectUserForm::checkCorrect(bool edit){
  bool create = true;

  id_user = ui->TB_id->text();
  if(ui->TB_name->text().size() < 3 || ui->TB_surname->text().size() < 3 || id_user.length() < 3 || id_user.contains(" ")) // 16 caratteri è giusto?
  {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Warning");
    msgBox.setText("One or more fields may be incomplete");
    msgBox.setInformativeText("First name, Last name and ID must have at least 3 letters");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
    return -1;
    }

    if(!edit && userList.findPos(id_user)>=0) // utente già presente
    {
      if(ui->TB_id->isReadOnly()) // sto modificando
          create = overWriteMsg("You will overwrite a user", "Are you sure?");
      else
          create = overWriteMsg("The user already exists", "Do you want overwrite?");

      return create * 2 -1; // -1 -> no save, 1 overwrite
    }
    return 0; // save
}

void SelectUserForm::createUser(bool overwrite){

    QString sex;
    if(ui->RB_male->isChecked())
      sex="Male";
    else if(ui->RB_female->isChecked())
      sex="Female";
    else
      sex="Other";

    QString dir;
    if(!overwrite){
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
      dir = userList.find(ui->TB_id->text())->getDir();
    }

    User u(dir,id_user,ui->TB_name->text(),ui->TB_surname->text(),ui->DE_birthday->date(), sex,
           ui->NB_height->value(), ui->NB_weight->value(), ui->NB_upperLeg->value(), ui->NB_lowerLeg->value());

    userList.add(u);

    QDir direct;
    if (!direct.exists(path+dir))
        direct.mkpath(path+dir);

    userList.saveXml(path + "users.xml");


    createComboBox(0,id_user);
}

void SelectUserForm::setReadOnly(bool status, bool id)
{
    ui->TB_name->setReadOnly(status);
    ui->TB_surname->setReadOnly(status);
    ui->TB_id->setReadOnly(id);
    ui->DE_birthday->setReadOnly(status);
    ui->RB_male->setEnabled(!status);
    ui->RB_female->setEnabled(!status);
    ui->RB_other->setEnabled(!status);
    ui->NB_height->setReadOnly(status);
    ui->NB_weight->setReadOnly(status);
    ui->NB_upperLeg->setReadOnly(status);
    ui->NB_lowerLeg->setReadOnly(status);
}

void SelectUserForm::editMode(bool edit)
{
    int size = 30 * edit; // true -> 1, fasle -> 0
    ui->BT_save->setMaximumHeight(size);
    ui->BT_cancel->setMaximumHeight(size);
    ui->BT_create->setMaximumHeight(30 - size);

    ui->BT_save->setMinimumHeight(size);
    ui->BT_cancel->setMinimumHeight(size);
    ui->BT_create->setMinimumHeight(30 - size);
}

void SelectUserForm::on_BT_selectUser_clicked()
{
    currentUser = userList.getAt(selectUser);
    frame_->customizeWindow(new TrainingForm(frame_.get(), userList.getAt(selectUser)));
    frame_->show();
}

void SelectUserForm::on_BT_viewLog_clicked()
{
    frame_->customizeWindow(new LogView(frame_.get(), ui->TB_id->text()));
    frame_->show();

    this->hide();
}

bool SelectUserForm::overWriteMsg(QString text, QString InformativeText){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Warning");
    msgBox.setText(text);
    msgBox.setInformativeText(InformativeText);
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();
    //if(ret == QMessageBox::Yes)
      //createUser(true);
    msgBox.close();
    return (ret == QMessageBox::Yes);
}

void SelectUserForm::on_finishButton_clicked()
{
  frame_->close();
}

void SelectUserForm::on_BT_save_clicked()
{
    if(checkCorrect(true) == 1)
        createUser(true);
}
