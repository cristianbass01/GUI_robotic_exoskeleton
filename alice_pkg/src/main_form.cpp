#include "main_form.h"
#include "ui_main_form.h"
#include "select_user_form.h"

#include "frame_window.h"
#include "training_form.h"
#include "global_variable.h"

MainForm::MainForm(FrameWindow *parent) :
  QWidget(parent),
  ui(new Ui::MainForm)
{
  frame_ = parent;
  ui->setupUi(this);
}

MainForm::~MainForm()
{
   delete ui;
}

/**
 * @brief visualizza la creazione di un nuovo utente
 */
void MainForm::on_BT_createUser_clicked()
{
    frame_->customizeWindow(new SelectUserForm(frame_, true));
    frame_->show();

    this->close();
}

/**
 * @brief visualizza i veri utenti e da la possibilità di selezionarne uno
 */
void MainForm::on_BT_selectUser_clicked()
{
    frame_->customizeWindow(new SelectUserForm(frame_));
    frame_->show();

    this->close();
}

/**
 * @brief Avvia l'esoscheletro in modalità Demo
 */
void MainForm::on_BT_demo_clicked()
{
    currentUser = nullptr;
    frame_->customizeWindow(new TrainingForm(frame_));
    frame_->show();

    this->close();
}

/**
 * @brief Chiude la schermata
 */
void MainForm::on_finishButton_clicked()
{
    frame_->close();
}
