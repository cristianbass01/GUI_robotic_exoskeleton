#ifndef CONTROL_FORM_H
#define CONTROL_FORM_H

#include <QWidget>

#include "session_form.h"
#include "frame_window.h"
#include <log.h>
#include <QTime>

namespace Ui {
class ControlForm;
}

class ControlForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlForm(SessionForm *parent = nullptr, Log *log = nullptr);
    ~ControlForm();

    void setEnabled(bool state);

private:
    Ui::ControlForm *ui;
    SessionForm *session_;
    FrameWindow *frame_;

    std::shared_ptr<Log> log_;
    int stepCount;
    void addLog(QString leg, bool correct, bool close, QTime time);
};

#endif // CONTROL_FORM_H
