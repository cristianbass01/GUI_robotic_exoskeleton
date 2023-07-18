#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QWidget>
#include <ros/ros.h>
#include "select_user_form.h"

#include "frame_window.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
  Q_OBJECT

public:
  explicit MainForm(FrameWindow *parent = nullptr);
  ~MainForm();

private slots:
    /**
    * @brief on_BT_createUser_clicked open select user form to create a user
    */
    void on_BT_createUser_clicked();

    /**
     * @brief on_BT_selectUser_clicked open select user form to select a user
     */
    void on_BT_selectUser_clicked();

    /**
     * @brief on_BT_demo_clicked open training form
     */
    void on_BT_demo_clicked();

    /**
     * @brief on_finishButton_clicked close application
     */
    void on_finishButton_clicked();

private:
    Ui::MainForm *ui;

    // reference to the parent frame
    FrameWindow *frame_;
};

#endif // MAIN_FORM_H
