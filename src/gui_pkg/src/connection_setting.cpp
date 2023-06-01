#include "connection_setting.h"
#include "ui_connection_setting.h"

connectionSetting::connectionSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connectionSetting)
{
    ui->setupUi(this);
}

connectionSetting::~connectionSetting()
{
    delete ui;
}
