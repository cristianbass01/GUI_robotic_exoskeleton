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

using namespace std;

CreateUserForm::CreateUserForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CreateUserForm)
{
  ui->setupUi(this);
}

CreateUserForm::~CreateUserForm()
{
  delete ui;
}

void CreateUserForm::on_BT_create_clicked()
{



  QString path("../../Exoskeleton/Users/");
  //QString path(QStandardPaths::locate(QStandardPaths::DesktopLocation, "") + ui->TB_cf->text() + "/");
  QDir dir; // Initialize to the desired dir if 'path' is relative
            // By default the program's working directory "." is used.

  // We create the directory if needed
  if (!dir.exists(path+ ui->TB_cf->text() + "/"))
      dir.mkpath(path + ui->TB_cf->text() + "/"); // You can check the success if needed

  QFile users(path + "users.csv");
  QFile info_user(path + ui->TB_cf->text() + "/info.csv");
  list<QString> users_name;
  if(users.open(QIODevice::ReadWrite)) { // Or QIODevice::ReadWrite
     QTextStream in(&users);
     while (!in.atEnd()) {
        users_name.push_back(in.readLine());
    }
  }
  users_name.push_back(ui->TB_cf->text());
  users_name.sort();
  users.close();

  users.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
  QTextStream user_writer(&users);
  while (users.size()>0) {
     user_writer << users_name.front();
     users_name.pop_front();

 }
  users.close();

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
         << ui->TB_cf->text() << ","        // Codice Fiscale
         << ui->DE_birthday->text() << ","  // Data Nascita
         << gender << ","                   // Genere
         << ui->NB_height->value();         // Altezza
            ;
  info_user.close();
}

void CreateUserForm::on_BT_test_clicked()
{
  SelectUserForm *suf = new SelectUserForm();
  //popupForm *pf2 = new popupForm(nullptr);

      suf->show();
      QObject::connect(suf, SIGNAL(on_BT_select_clicked()), this, SLOT(test_Dialog()));

      //QMessageBox::information(this,"ok","ok");
}

void CreateUserForm::test_Dialog()
{
  QMessageBox::information(this,"ok","ok");
}
