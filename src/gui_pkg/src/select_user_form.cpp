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
#include <dialog_form.h>
#include <log_view.h>
#include <training_form.h>

SelectUserForm::SelectUserForm(FrameWindow *parent, bool create) :
  QWidget(parent), ui(new Ui::SelectUserForm)
{
    frame_ = parent;
    ui->setupUi(this);

    createComboBox(!create, NULL);
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
        currentUser = users[index-1].second;
        u = userList.getAt(currentUser);
        ui->BT_create->setText("Edit");

    }
    else {
        ui->BT_create->setText("Save");
    }

    if(u==nullptr) {
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
    bool create = true;
    bool edit = false;

  if(ui->BT_create->text()=="Edit"){
      setReadOnly(false, true);
      ui->BT_create->setText("Save");
      edit = true;
  }

  id_user = ui->TB_id->text();
  if(ui->TB_name->text().size() < 3 || ui->TB_surname->text().size() < 3 || id_user.length() < 3 || id_user.contains(" ")) // 16 caratteri è giusto?
  {
    QMessageBox::warning(this,"Warning", "One or more fields may be incomplete\n\nFirst name, Last name and ID must have at least 3 letters");
    return;
  }

  if(!edit && userList.findPos(id_user)>=0) // utente già presente
  {
    DialogForm *dial = new DialogForm(); // form per la sovrascrizione
    dial->show();
    QObject::connect(dial, SIGNAL(on_BT_dialog_accepted()), this, SLOT(createUser()));
    create = false;
  }
  if(!edit && create)
      createUser();
}

void SelectUserForm::createUser(){

    QString sex;
    if(ui->RB_male->isChecked())
      sex="Male";
    else if(ui->RB_female->isChecked())
      sex="Female";
    else
      sex="Other";

    QString dir = "a000";
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

    User u(dir,id_user,ui->TB_name->text(),ui->TB_surname->text(),ui->DE_birthday->date(), sex,
           ui->NB_height->value(), ui->NB_weight->value(), ui->NB_upperLeg->value(), ui->NB_lowerLeg->value());

    userList.add(u);

    QDir direct;
    if (!direct.exists(path+dir))
        direct.mkpath(path+dir);

    userList.saveXml(path + "users.xml");


    createComboBox(0,id_user);
}

void SelectUserForm::rejected()
{
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

void SelectUserForm::on_BT_selectUser_clicked()
{
  frame_->customizeWindow(new TrainingForm(frame_, userList.getAt(currentUser)));
  frame_->show();

}

void SelectUserForm::on_BT_viewLog_clicked()
{
  frame_->customizeWindow(new LogView(frame_, ui->TB_id->text()));
  frame_->show();

  this->hide();
}
