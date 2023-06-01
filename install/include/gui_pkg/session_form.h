#ifndef WALKING_WINDOW_H
#define WALKING_WINDOW_H

#include <QWidget>
#include "connected_component.h"
#include "frame_window.h"
#include "user.h"

namespace Ui {
class SessionForm;
}

class SessionForm : public QWidget
{
    Q_OBJECT

public:
    explicit SessionForm(FrameWindow * parent = nullptr, User *user = nullptr);
    ~SessionForm();

    void customizeForm(QWidget *widget_to_insert);
    FrameWindow *getFrame(){return this->frame_;}

    void setConnected(bool state);

    void displayUser();

    void movement(const std::string code);

    void setEnabled(bool state);

    void setImage(const QString);

    const QString LEFTSTEP = QString::fromStdString(":/Alice/Alice/Alice_left_step.png");
    const QString RIGHTSTEP = QString::fromStdString(":/Alice/Alice/Alice_right_step.png");
    const QString LEFTCLOSE = QString::fromStdString(":/Alice/Alice/Alice_step_five.png");
    const QString SIT = QString::fromStdString(":/Alice/Alice/Alice_sit_straight.png");
    const QString STORAGE = QString::fromStdString(":/Alice/Alice/Alice_sitting_exercises.png");
    const QString STAND = QString::fromStdString(":/Alice/Alice/Alice_stand_straight.png");
    const QString NOTCONNECTED = QString::fromStdString(":/Alice/Alice/Alice_not_connected.png");

public slots:

    void on_connectButton_clicked();

private slots:
    void on_controlWindowButton_clicked();

    void on_stepWindowButton_clicked();

    void on_returnButton_clicked();

    void on_walkWindowButton_clicked();

    void on_sitButton_clicked();

    void on_storageButton_clicked();

    void on_standButton_clicked();

private:
    Ui::SessionForm *ui;
    FrameWindow * frame_;
    User *user_;

    QWidget *form_ = nullptr;
};

#endif // WALKING_WINDOW_H
