#ifndef WALKING_FORM_H
#define WALKING_FORM_H

#include <QWidget>
#include "session_form.h"
#include "frame_window.h"
#include <log.h>
#include <QTime>

namespace Ui {
class WalkingForm;
}

class WalkingForm : public QWidget
{
    Q_OBJECT

public:
    explicit WalkingForm(SessionForm *parent = nullptr, Log *log = nullptr);
    ~WalkingForm();

private:
    Ui::WalkingForm *ui;
    SessionForm *session_;
    FrameWindow *frame_;

    Log *log_;

    void addLog(int set, int executed, int pause, QTime time);
};

#endif // WALKING_FORM_H
