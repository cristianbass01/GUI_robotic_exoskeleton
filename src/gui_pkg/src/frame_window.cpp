#include "frame_window.h"
#include "ui_frame_window.h"

#include "main_form.h"
#include "session_form.h"
#include "training_form.h"
#include <global_variable.h>
#include <QMessageBox>
#include "log_view.h"

#include "connection_setting.h"

FrameWindow::FrameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrameWindow)
{
    ui->setupUi(this);
    ui->statusBar->hide();
}

FrameWindow::~FrameWindow()
{
    delete ui;
}

void FrameWindow::customizeWindow(QWidget *widget_to_insert){
    auto last = ui->parentLayout->takeAt(0);
    if(last){
        ui->parentLayout->removeWidget(last->widget());
        last->widget()->close();
    }

    currentForm = widget_to_insert->objectName();
    ui->parentLayout->addWidget(widget_to_insert);
}

void FrameWindow::setConnected(bool state){
    if (ui->parentLayout->takeAt(0)){
        if(currentForm.toStdString().compare("SessionForm") == 0)
            qobject_cast<SessionForm *>( ui->parentLayout->takeAt(0)->widget())->setConnected(state);
        else
            qobject_cast<TrainingForm *>( ui->parentLayout->takeAt(0)->widget())->setConnected(state);
    }
}

void FrameWindow::on_actionHome_triggered()
{
    this->customizeWindow(new MainForm(this));
}

void FrameWindow::on_actionClose_triggered()
{
    this->close();
}

void FrameWindow::on_actionDemo_triggered()
{
    currentUser = nullptr;
    this->customizeWindow(new TrainingForm(this));
}

void FrameWindow::on_actionNew_User_triggered()
{
    this->customizeWindow(new SelectUserForm(this, true));
}

void FrameWindow::on_actionView_User_triggered()
{
    this->customizeWindow(new SelectUserForm(this, false, (currentUser == nullptr)? nullptr : currentUser->getId()));
}

void FrameWindow::on_actionEdit_User_triggered()
{
  if(currentUser == nullptr)
  {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Warning");
    msgBox.setText("No user select");
    msgBox.setInformativeText("Please select a user first");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
  }

  else {
    SelectUserForm* selec = new SelectUserForm(this, false, currentUser->getId());
    selec->setEditMode();
    this->customizeWindow(selec);
  }
}

void FrameWindow::on_actionMaximize_Window_triggered()
{
    this->showMaximized();
}

void FrameWindow::on_actionTraining_triggered()
{
  if(currentUser == nullptr)
  {
      QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::Warning);
      msgBox.setWindowTitle("Warning");
      msgBox.setText("No user select");
      msgBox.setInformativeText("Please select a user first");
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.exec();
  }
  else
      this->customizeWindow(new TrainingForm(this));
}

void FrameWindow::on_actionTraining_Log_triggered()
{
  if(currentUser == nullptr)
      this->customizeWindow(new LogView(this, ""));
  else
      this->customizeWindow(new LogView(this, currentUser->getId()));
}

void FrameWindow::on_actionChange_settings_triggered()
{
    ConnectionSetting * form = new ConnectionSetting(nullptr, false);
    form->exec();
}


void FrameWindow::on_actionView_triggered()
{
    ConnectionSetting * form = new ConnectionSetting(nullptr, true);
    form->exec();
}

void FrameWindow::on_actionInfo_triggered()
{
    QMessageBox::information(nullptr,"Information", "This application was designed as a bachelor thesis by Cristian Bassotto and Nicola Busato");
}

void FrameWindow::on_actionHelp_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText("This is just a prototipe.");
    msgBox.setInformativeText("For more information, visit <a href=\"https://github.com/cristianbass01/GUI_robotic_exoskeleton.git\">GUI_robotic_exoskeleton</a>.");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();
}

void FrameWindow::setEnabled(bool state){
    ui->toolBar->setEnabled(state);
    ui->menubar->setEnabled(state);
}

void FrameWindow::showStatus(std::string msg){
    ui->statusBar->show();
    ui->statusBar->showMessage(QString::fromStdString(msg));
}

void FrameWindow::clearStatus(){
    ui->statusBar->clearMessage();
    ui->statusBar->hide();
}
