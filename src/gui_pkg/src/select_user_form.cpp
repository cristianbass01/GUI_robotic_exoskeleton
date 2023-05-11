#include "select_user_form.h"
#include "ui_select_user_form.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QMessageBox>
#include <QStandardPaths>

#include <user_list.h>
#include <global_user_list.h>

SelectUserForm::SelectUserForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SelectUserForm)
{
  ui->setupUi(this);


  QFile users(path + "users.csv");

  //users_list.clear();
  QString s;

  if(users.open(QIODevice::ReadWrite)) { // Or QIODevice::ReadWrite
     QTextStream in(&users);
     while (!in.atEnd()) {
        s = in.readLine();
        //users_list.push_back(s);
        ui->CB_selectUser->addItem(s);
    }
  }
  users.close();

}

SelectUserForm::~SelectUserForm()
{
  delete ui;
}

void SelectUserForm::on_CB_selectUser_currentIndexChanged(const QString &arg1)
{
    QString s;
    QFile user(path + arg1 + "/info.csv");
    if(user.open(QIODevice::ReadOnly)) { // Or QIODevice::ReadWrite
       QTextStream in(&user);
       while (!in.atEnd()) {
          s = in.readLine(); //! da controllare se legge
      }
    }
    else {
      QMessageBox::warning(this,"Attenzione","L'utente selezionato non è presente"); //// come proseguo? elimino dal file, o chiedo di recrearlo?
    }
    user.close();
    QList<QString> info = s.split(",");

    ui->TB_name->setText(info[0]);
    ui->TB_surname->setText(info[1]);
    ui->TB_cf->setText(info[2]);
    ui->DE_birthday->setDate(QDate::fromString(info[3],"dd/MM/yyyy"));
    switch ((info[4].toStdString())[0]) {
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
    ui->NB_height->setValue(info[5].toInt());
}
