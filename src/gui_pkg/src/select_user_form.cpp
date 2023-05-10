#include "select_user_form.h"
#include "ui_select_user_form.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QMessageBox>
#include <QStandardPaths>

SelectUserForm::SelectUserForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SelectUserForm)
{
  ui->setupUi(this);


  QFile users(path + "users.csv");

  QList<QString> users_list;

  if(users.open(QIODevice::ReadWrite)) { // Or QIODevice::ReadWrite
     QTextStream in(&users);
     while (!in.atEnd()) {
        users_list.push_back(in.readLine());

    }
  }
  users.close();

}

SelectUserForm::~SelectUserForm()
{
  delete ui;
}
