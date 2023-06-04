#include "connection_setting.h"
#include "ui_connection_setting.h"

#include "global_variable.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QListWidget>
#include <QTableWidget>
#include <QVector>
#include <list>

ConnectionSetting::ConnectionSetting(QWidget *parent, bool onlyView) :
    QDialog(parent),
    ui(new Ui::ConnectionSetting)
{
    ui->setupUi(this);
    this->setup(onlyView);
}

ConnectionSetting::~ConnectionSetting()
{
    delete ui;
}

void ConnectionSetting::on_closeButton_clicked()
{
    this->close();
}

void ConnectionSetting::on_changeButton_clicked()
{
    this->setup(false);
}


void ConnectionSetting::on_discardButton_clicked()
{
    this->close();
}

void ConnectionSetting::on_saveButton_clicked()
{
    bool retry = false;
    if(connectedComponent->isConnected()){
        for(int i = 0; i < ui->formLayout->rowCount(); i++){
            QFormLayout::TakeRowResult row = ui->formLayout->takeRow(i);
            std::string param_name = qobject_cast<QLabel*>(row.labelItem->widget())->text().toStdString();
            //std::string new_param_value = qobject_cast<QLineEdit*>(row.fieldItem->widget())->text().toStdString();
            ui->formLayout->insertRow(i, row.labelItem->widget(), row.fieldItem->widget());


            XmlRpc::XmlRpcValue param_value = connectedComponent->getParam(param_name);
            XmlRpc::XmlRpcValue new_param_value;

            // Determina il tipo di parametro
            if (param_value.getType() == XmlRpc::XmlRpcValue::TypeInt) {
                new_param_value = qobject_cast<QSpinBox*>(row.fieldItem->widget())->value();

            } else if (param_value.getType() == XmlRpc::XmlRpcValue::TypeDouble) {
                new_param_value = qobject_cast<QDoubleSpinBox*>(row.fieldItem->widget())->value();

            } else if (param_value.getType() == XmlRpc::XmlRpcValue::TypeString) {
                new_param_value = qobject_cast<QLineEdit*>(row.fieldItem->widget())->text().toStdString();

            } else if (param_value.getType() == XmlRpc::XmlRpcValue::TypeArray) {
                QListWidget* list = qobject_cast<QListWidget*>(row.fieldItem->widget());


                int itemCount = list->count();
                new_param_value.setSize(itemCount);

                // Riserva la capacità per evitare riallocazioni
                for (int row = 0; row < itemCount; ++row) {
                    new_param_value[row] = (list->item(row)->text().toStdString());
                }


            } else if (param_value.getType() == XmlRpc::XmlRpcValue::TypeStruct) {
                QTableWidget* table = qobject_cast<QTableWidget*>(row.fieldItem->widget());
                int itemCount = table->rowCount();
                new_param_value.setSize(itemCount);

                for (int row = 0; row < itemCount; ++row) {
                    std::string key = table->item(row, 0)->text().toStdString();
                    std::string value = table->item(row, 1)->text().toStdString();
                    new_param_value[key] = value;
                }

            } else if (param_value.getType() == XmlRpc::XmlRpcValue::TypeBoolean) {
                new_param_value = qobject_cast<QCheckBox*>(row.fieldItem->widget())->isChecked();

            }
            else {
                ROS_WARN("Il tipo del parametro %s non è gestito.", param_name.c_str());
            }

            if(!connectedComponent->setParam(param_name, new_param_value)){
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setWindowTitle("Parameter Error");
                msgBox.setText(QString::fromStdString("Wrong parameter value of " + param_name + " = " + new_param_value.toXml() + "\n"));
                msgBox.setStandardButtons(QMessageBox::Ok);

                int ret = msgBox.exec();

                retry = true;

                if (ret == QMessageBox::Ok) {
                    // Retry button clicked
                    // Add your retry logic here
                    msgBox.close();
                }
            }
        }
    }

    if(!retry)
        this->close();
}

void ConnectionSetting::setup(bool readOnly){

    //this->hide();

    QApplication::processEvents();

    // Rimuovi tutte le righe
    for(int row = ui->formLayout->rowCount()-1; row >=0 ; row--) {
       ui->formLayout->removeRow(row);

        //delete item;
    }

    if(connectedComponent->isConnected()){
        std::vector<std::string> paramsList = connectedComponent->getParamsList();
        for(std::string param_name : paramsList){

            XmlRpc::XmlRpcValue param_value = connectedComponent->getParam(param_name);

            // Determina il tipo di parametro
            if (param_value.getType() == XmlRpc::XmlRpcValue::TypeInt) {
                ROS_INFO("Il parametro %s è di tipo int.", param_name.c_str());
                QLabel *label = new QLabel(QString::fromStdString(param_name));
                QSpinBox * field = new QSpinBox();
                field->setValue(param_value);
                field->setReadOnly(readOnly);
                ui->formLayout->addRow(label, field);
            } else if (param_value.getType() == XmlRpc::XmlRpcValue::TypeDouble) {
                ROS_INFO("Il parametro %s è di tipo double.", param_name.c_str());
                QLabel *label = new QLabel(QString::fromStdString(param_name));
                QDoubleSpinBox * field = new QDoubleSpinBox();
                field->setValue(param_value);
                field->setReadOnly(readOnly);
                ui->formLayout->addRow(label, field);
            } else if (param_value.getType() == XmlRpc::XmlRpcValue::TypeString) {
                ROS_INFO("Il parametro %s è di tipo string.", param_name.c_str());
                QLabel* label = new QLabel(QString::fromStdString(param_name));
                QLineEdit* lineEdit = new QLineEdit();
                lineEdit->setText(QString::fromStdString(param_value));
                lineEdit->setReadOnly(readOnly);
                ui->formLayout->addRow(label, lineEdit);
            } else if (param_value.getType() == XmlRpc::XmlRpcValue::TypeArray) {
                ROS_INFO("Il parametro %s è di tipo vector.", param_name.c_str());
                QLabel* label = new QLabel(QString::fromStdString(param_name));
                QListWidget *field = new QListWidget();
                for(int i = 0; i < param_value.size(); ++i){
                    if (param_value[i].getType() == XmlRpc::XmlRpcValue::TypeString) {
                        std::string value = static_cast<std::string>(param_value[i]);
                        QString itemText = QString::fromStdString(value);
                        field->addItem(itemText);
                    }
                }
                if(readOnly)
                    field->setEditTriggers(QAbstractItemView::NoEditTriggers);
                else
                    field->setEditTriggers(QAbstractItemView::DoubleClicked);
                ui->formLayout->addRow(label, field);
            } else if (param_value.getType() == XmlRpc::XmlRpcValue::TypeStruct) {
                ROS_INFO("Il parametro %s è di tipo map.", param_name.c_str());
                QLabel* label = new QLabel(QString::fromStdString(param_name));
                QTableWidget* field = new QTableWidget();
                field->setRowCount(param_value.size());
                field->setColumnCount(2);
                int row = 0;
                for (auto pair : param_value) {
                    QTableWidgetItem* keyItem = new QTableWidgetItem(QString::fromStdString(pair.first));
                    QTableWidgetItem* valueItem = new QTableWidgetItem(QString::fromStdString(static_cast<std::string>(pair.second)));
                    field->setItem(row, 0, keyItem);
                    field->setItem(row, 1, valueItem);
                    ++row;
                }
                if(readOnly)
                    field->setEditTriggers(QAbstractItemView::NoEditTriggers);
                else
                    field->setEditTriggers(QAbstractItemView::DoubleClicked);
                ui->formLayout->addRow(label, field);
            } else if (param_value.getType() == XmlRpc::XmlRpcValue::TypeBoolean) {
                ROS_INFO("Il parametro %s è di tipo boolean.", param_name.c_str());
                QLabel* label = new QLabel(QString::fromStdString(param_name));
                QCheckBox *field = new QCheckBox();
                if(param_value)
                    field->setChecked(true);
                else
                    field->setChecked(false);

                if (readOnly) {
                    field->setEnabled(false);  // Disabilita la checkbox
                } else {
                    field->setEnabled(true);   // Abilita la checkbox
                }
                ui->formLayout->addRow(label, field);
            }
            else {
                ROS_WARN("Il tipo del parametro %s non è gestito.", param_name.c_str());
            }
        }
    }

    if(readOnly){
        ui->changePage->hide();
        ui->viewPage->show();
    } else{
        ui->changePage->show();
        ui->viewPage->hide();
    }

    //this->show();
}
