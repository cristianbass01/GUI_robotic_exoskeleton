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
  cf = ui->TB_cf->text();
  if(ui->TB_name->text().size() < 3 || ui->TB_surname->text().size() < 3 || cf.length() != 16)
  {
    QMessageBox::warning(this,"Attenzione","Uno o più campi potrebbero essere incompleti\n\nNome e Cognome devono avere almeno 3 lettre, e il CF composto da 16");
    return;
  }

  createUser();

  //Per ora niente ricerca se è già presente
  /*
  QFile users(path + "users.csv");
  //QString p = QStandardPaths::HomeLocation + "/log";
  QString s;

  users_list.clear();
  if(users.open(QIODevice::ReadWrite)) { // Or QIODevice::ReadWrite
     QTextStream in(&users);
     while (!in.atEnd()) {
        s = in.readLine();
        users_list.push_back(s);
        if(!QString::compare(cf,s))
        {
          DialogForm *dial = new DialogForm();
          dial->show();
          QObject::connect(dial, SIGNAL(on_BT_dialog_rejected()), this, SLOT(rejected()));
          QObject::connect(dial, SIGNAL(on_BT_dialog_accepted()), this, SLOT(createUser()));
          create = false;
        }
    }
  }
  if(create)
      createUser();
  users.close();
  */
}

void CreateUserForm::rejected()
{
  //QMessageBox::information(this,"ok","ok");
}

void CreateUserForm::createUser(){

    QString sex;
    if(ui->RB_male->isChecked())
      sex="Male";
    else if(ui->RB_female->isChecked())
      sex="Female";
    else
      sex="Other";

    QString dir = "aa000";

    User u(dir,cf,ui->TB_name->text(),ui->TB_surname->text(),ui->DE_birthday->date(), sex,
                       ui->NB_height->value(), ui->NB_height->value(), ui->NB_femur->value(), ui->NB_tibia->value());

    userList.add(u);

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
