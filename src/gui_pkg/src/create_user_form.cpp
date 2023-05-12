#include "create_user_form.h"
#include "ui_create_user_form.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QMessageBox>
#include <QStandardPaths>

#include "dialog_form.h"
#include "select_user_form.h"
#include <main_form.h>
#include <global_variable.h>

using namespace std;

CreateUserForm::CreateUserForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CreateUserForm)
{
  ui->setupUi(this);
  //QString path;
  QDir dir;
  if (!dir.exists(path))
      dir.mkpath(path); // You can check the success if needed
}

CreateUserForm::~CreateUserForm()
{
  delete ui;
}

void CreateUserForm::closeEvent (QCloseEvent *event)
{
  //parent->show();
}

void CreateUserForm::on_BT_create_clicked()
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

void CreateUserForm::rejected()
{
}

void CreateUserForm::createUser(){

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


    QMessageBox::information(this,"Informazioni","Utente creato correttamente.\nPuoi chiudere questa scheda");
}

void CreateUserForm::on_BT_selectUser_clicked()
{
  SelectUserForm *SelectUserF = new SelectUserForm();
  SelectUserF->show();

  this->hide();
  this->deleteLater();
}
