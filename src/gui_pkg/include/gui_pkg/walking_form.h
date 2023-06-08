#ifndef WALKING_FORM_H
#define WALKING_FORM_H

#include <QWidget>
#include "session_form.h"
#include "frame_window.h"
#include <log.h>
#include <QTime>
#include "walk_thread.h"

namespace Ui {
class WalkingForm;
}

class WalkingForm : public QWidget
{
    Q_OBJECT

public:
    explicit WalkingForm(SessionForm *parent = nullptr, Log *log = nullptr);
    ~WalkingForm();

    void setEnabled(bool state);

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void updateProgressBar(int value);

    void finishProgressBar();

private:
    Ui::WalkingForm *ui;
    SessionForm *session_;
    FrameWindow *frame_;

    Log* log_;
    QSharedPointer<WalkThread> thread_;


};

#endif // WALKING_FORM_H
