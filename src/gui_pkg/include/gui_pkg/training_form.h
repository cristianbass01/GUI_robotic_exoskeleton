#ifndef TRAINING_WINDOW_H
#define TRAINING_WINDOW_H

#include <QWidget>
#include "frame_window.h"

#include <log.h>
#include "user.h"


namespace Ui {
class TrainingForm;
}

class TrainingForm : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingForm(FrameWindow *parent = nullptr, User *user = nullptr);
    ~TrainingForm();

    FrameWindow* getFrame(){return this->frame_;}
    void setConnected(bool state);

    void displayUser();


private slots:
    void on_standButton_clicked();

    void on_stepButton_clicked();

    void on_walkButton_clicked();

    void on_controlButton_clicked();

    void on_finishButton_clicked();

    void on_connectButton_clicked();

private:
    Ui::TrainingForm *ui;
    FrameWindow *frame_;
    User *user_;

    QSharedPointer<Log> log;

    //FrameWindow *frame_;

    //Log *log;

};

#endif // TRAINING_WINDOW_H
