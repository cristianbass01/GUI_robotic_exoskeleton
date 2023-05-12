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

SelectUserForm::SelectUserForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SelectUserForm)
{
  ui->setupUi(this);

  QList<QString> users;

  for(int i = 0; i<userList.size(); i++) {
    User* u = userList.getAt(i);
    users.append(u->getSurname() + " " + u->getName() + " " +u->getId());
  }
  qSort(users);
  ui->CB_selectUser->addItems(users);
}

SelectUserForm::~SelectUserForm()
{
  delete ui;
}

void SelectUserForm::on_CB_selectUser_currentIndexChanged(const QString &arg1)
{
  QStringList tokens = arg1.split(" ");
  QString id = tokens.at(tokens.size()-1);
  User* u = userList.find(id);

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
