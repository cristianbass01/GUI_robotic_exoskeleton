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
    FrameWindow *getFrame(){return this->frame_.get();}

    void setConnected(bool state);

    void displayUser();

public slots:
    void on_controlWindowButton_clicked();

    void on_stepWindowButton_clicked();

    void on_returnButton_clicked();

    void on_walkWindowButton_clicked();

    void on_connectButton_clicked();

private:
    Ui::SessionForm *ui;
    std::shared_ptr<FrameWindow> frame_;
    std::shared_ptr<User> user_;
};

#endif // WALKING_WINDOW_H
