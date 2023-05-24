#ifndef STEP_FORM_H
#define STEP_FORM_H

#include <QWidget>
#include "session_form.h"
#include "frame_window.h"

namespace Ui {
class StepForm;
}

class StepForm : public QWidget
{
    Q_OBJECT

public:
    explicit StepForm(SessionForm *parent = nullptr);
    ~StepForm();

private slots:
    void on_leftFirstStepButton_clicked();

    void on_rightFirstStepButton_clicked();

    void on_feetTogetherButton_clicked();

private:
    Ui::StepForm *ui;
    SessionForm *session_;
    FrameWindow *frame_;
};

#endif // STEP_FORM_H
