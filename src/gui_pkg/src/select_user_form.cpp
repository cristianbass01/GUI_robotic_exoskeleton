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

SelectUserForm::SelectUserForm(QWidget *parent, bool create) :
  QWidget(parent), ui(new Ui::SelectUserForm)
{
    ui->setupUi(this);

    createComboBox(!create, NULL);
}

SelectUserForm::~SelectUserForm()
{
    delete ui;
}

void SelectUserForm::createComboBox(int start, QString id){
  ui->CB_selectUser->clear();

  ui->CB_selectUser->addItem(QString("- - - Create User - - -"));

  QList<QString> users;

  for(int i = 0; i<userList.size(); i++) {
    User* u = userList.getAt(i);
    users.append(u->getSurname() + " " + u->getName() + " " +u->getId());
  }
  qSort(users);

  QStringList tokens;
  QString u_id;

  for(int i = 0; i<users.size(); i++) {
    tokens = users.at(i).split(" ");
    u_id = tokens.at(tokens.size()-1);
      if(!QString::compare(u_id,id))
        start = i + 1;
  }

  ui->CB_selectUser->addItems(users);

  ui->CB_selectUser->setCurrentIndex(start);
}

void SelectUserForm::on_CB_selectUser_currentIndexChanged(const QString &arg1)
{
    setReadOnly(ui->CB_selectUser->currentIndex()!=0);

    User* u = new User;
    if(ui->CB_selectUser->currentIndex()>0)
    {
        QStringList tokens = arg1.split(" ");
        QString id = tokens.at(tokens.size()-1);
        u = userList.find(id);
        ui->BT_create->setText("Edit");
    }
    else {
        ui->BT_create->setText("Save");
    }

    if(u==nullptr) {
      QMessageBox::warning(this,"Attenzione","L'utente selezionato non è presente");
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
    ui->NB_femur->setValue(u->getFemur());
    ui->NB_tibia->setValue(u->getTibia());
}

void SelectUserForm::on_BT_create_clicked()
{
  bool create = true;
  id_user = ui->TB_id->text();
  if(ui->TB_name->text().size() < 3 || ui->TB_surname->text().size() < 3 || id_user.length() != 16 || id_user.contains(" ")) // 16 caratteri è giusto?
  {
    QMessageBox::warning(this,"Attenzione","Uno o più campi potrebbero essere incompleti\n\nNome e Cognome devono avere almeno 3 lettre, e il CF composto da 16");
    return;
  }

  if(userList.findPos(id_user)>=0) // utente già presente
  {
    DialogForm *dial = new DialogForm();
    dial->show();
    QObject::connect(dial, SIGNAL(on_BT_dialog_accepted()), this, SLOT(createUser()));
    create = false;
  }
  if(create)
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
           ui->NB_height->value(), ui->NB_weight->value(), ui->NB_femur->value(), ui->NB_tibia->value());

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

void SelectUserForm::setReadOnly(bool status)
{
  ui->TB_name->setReadOnly(status);
  ui->TB_surname->setReadOnly(status);
  ui->TB_id->setReadOnly(status);
  ui->DE_birthday->setReadOnly(status);
  ui->RB_male->setEnabled(!status);
  ui->RB_female->setEnabled(!status);
  ui->RB_other->setEnabled(!status);
  ui->NB_height->setReadOnly(status);
  ui->NB_weight->setReadOnly(status);
  ui->NB_femur->setReadOnly(status);
  ui->NB_tibia->setReadOnly(status);
}

void SelectUserForm::on_BT_selectUser_clicked()
{

}
