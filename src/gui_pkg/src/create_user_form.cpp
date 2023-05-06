#include "create_user_form.h"
#include "ui_create_user_form.h"
#include <QDir>
#include <QFile>
#include <QTextStream>

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

  QString path("../../Users/"+ ui->TB_cf->text() + "/");
  QDir dir; // Initialize to the desired dir if 'path' is relative
            // By default the program's working directory "." is used.

  // We create the directory if needed
  if (!dir.exists(path))
      dir.mkpath(path); // You can check the success if needed

  QFile file(path + "info.csv");
  file.open(QIODevice::WriteOnly); // Or QIODevice::ReadWrite
  QTextStream stream(&file);
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
  file.close();
}
