#ifndef WALKING_FORM_H
#define WALKING_FORM_H

#include <QWidget>
#include "session_form.h"
#include "frame_window.h"

namespace Ui {
class WalkingForm;
}

class WalkingForm : public QWidget
{
    Q_OBJECT

public:
    explicit WalkingForm(SessionForm *parent = nullptr);
    ~WalkingForm();

private:
    Ui::WalkingForm *ui;
    SessionForm *session_;
    FrameWindow *frame_;
};

#endif // WALKING_FORM_H
