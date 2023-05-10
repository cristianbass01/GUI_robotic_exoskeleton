#include "create_user_form.h"
#include "ui_create_user_form.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QMessageBox>
#include <select_user_form.h>

#include <QStandardPaths>
#include <list>
#include <dialog_form.h>

using namespace std;

CreateUserForm::CreateUserForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CreateUserForm)
{
  ui->setupUi(this);

  QDir dir;
  if (!dir.exists(path))
      dir.mkpath(path); // You can check the success if needed
}

CreateUserForm::~CreateUserForm()
{
  delete ui;
}

void CreateUserForm::on_BT_create_clicked()
{
  QString cf = ui->TB_cf->text();
  if(ui->TB_name->text().size() < 3 || ui->TB_surname->text().size() < 3 || cf != 16)
  {
    QMessageBox::warning(this,"Attenzione","Uno o più campi potrebbero essere incompleti\n\nNome e Cognome devono avere almeno 3 lettre, e il CF composto da 16");
    return;
  }

  QDir dir; // Initialize to the desired dir if 'path' is relative
            // By default the program's working directory "." is used.


  QFile users(path + "users.csv");

  QString s;

  list<QString> users_list;
  if(users.open(QIODevice::ReadWrite)) { // Or QIODevice::ReadWrite
     QTextStream in(&users);
     while (!in.atEnd()) {
        s = in.readLine();
        users_list.push_back(s);
        if(QString::compare(cf,s))
        {
            
        }

    }
  }


  users_list.push_back(cf);
  // We create the directory if needed
  if (!dir.exists(path+ cf + "/"))
      dir.mkpath(path + cf + "/"); // You can check the success if needed


  users_list.sort();
  users.close();

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
  QString gender;
  if(ui->RB_male->isChecked())
    gender="Maschio";
  else if(ui->RB_female->isChecked())
    gender="Femmina";
  else
    gender="Altro";

  stream << ui->TB_name->text() << ","      // Nome
         << ui->TB_surname->text() << ","   // Cognome
         << cf << ","                       // Codice Fiscale
         << ui->DE_birthday->text() << ","  // Data Nascita
         << gender << ","                   // Genere
         << ui->NB_height->value();         // Altezza
            ;
  info_user.close();
}

void CreateUserForm::on_BT_test_clicked()
{
  //SelectUserForm *suf = new SelectUserForm();

  DialogForm *dial = new DialogForm();
  //popupForm *pf2 = new popupForm(nullptr);

  dial->show();
  QObject::connect(dial, SIGNAL(on_buttonBox_accepted()), this, SLOT(test_Dialog()));

      //QMessageBox::information(this,"ok","ok");
}

void CreateUserForm::test_Dialog()
{
  QMessageBox::information(this,"ok","ok");
}
