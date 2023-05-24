#ifndef CONTROL_FORM_H
#define CONTROL_FORM_H

#include <QWidget>

#include "session_form.h"
#include "frame_window.h"

namespace Ui {
class ControlForm;
}

class ControlForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlForm(SessionForm *parent = nullptr);
    ~ControlForm();

private:
    Ui::ControlForm *ui;
    SessionForm *session_;
    FrameWindow *frame_;
};

#endif // CONTROL_FORM_H
