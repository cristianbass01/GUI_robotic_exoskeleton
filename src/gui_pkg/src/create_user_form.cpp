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
  id_user = ui->TB_cf->text();
  if(ui->TB_name->text().size() < 3 || ui->TB_surname->text().size() < 3 || id_user.length() != 16)
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


    User *userToModify = userList.find(id_user);
    if(userToModify!=nullptr)
    {
      //userToModify->setDir(dir);
      //userToModify->setId(id_user);
      userToModify->setName(ui->TB_name->text());
      userToModify->setSurname(ui->TB_surname->text());
      userToModify->setBirthday(ui->DE_birthday->date());
      userToModify->setSex(sex);
      userToModify->setHeight(ui->NB_height->value());
      userToModify->setWeight(ui->NB_weight->value());
      userToModify->setFemur(ui->NB_femur->value());
      userToModify->setTibia(ui->NB_tibia->value());
    }
    else {
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
             ui->NB_height->value(), ui->NB_height->value(), ui->NB_femur->value(), ui->NB_tibia->value());

      userList.add(u);
    }

    userList.saveXml(path + "users.xml");

    /*

    QDir dir; // Initialize to the desired dir if 'path' is relative
            // By default the program's working directory "." is used.

    // We create the directory if needed
    if (!dir.exists(path+ cf + "/"))
        dir.mkpath(path + cf + "/"); // You can check the success if needed

    //users_list.sort();
    if(!users_list.contains(cf))
        users_list.push_back(cf);

    //users_list.removeDuplicates(); // nel caso dovessi reinserire lo stesso utente

    QFile users(path + "users.csv");
    users.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream user_writer(&users);
    while (users_list.size()>0) {
       user_writer << users_list.front() << "\n";
       users_list.pop_front();

    }
    users.close();

    QFile info_user(path + ui->TB_cf->text() + "/info.csv");
    info_user.open(QIODevice::WriteOnly); // Or QIODevice::ReadWrite

    QTextStream stream(&info_user);


    stream << ui->TB_name->text() << ","      // Nome
           << ui->TB_surname->text() << ","   // Cognome
           << cf << ","                       // Codice Fiscale
           << ui->DE_birthday->text() << ","  // Data Nascita
           << gender << ","                   // Genere
           << ui->NB_height->value();         // Altezza
              ;
    info_user.close();
    */

    QMessageBox::information(this,"Informazioni","Utente creato correttamente.\nPuoi chiudere questa scheda");
}

void CreateUserForm::on_BT_selectUser_clicked()
{
  SelectUserForm *SelectUserF = new SelectUserForm();
  SelectUserF->show();

  this->hide();
  this->deleteLater();
}
