#ifndef STEP_FORM_H
#define STEP_FORM_H

#include <QWidget>
#include "session_form.h"
#include "frame_window.h"
#include <log.h>

namespace Ui {
class StepForm;
}

class StepForm : public QWidget
{
    Q_OBJECT

public:
    explicit StepForm(SessionForm *parent = nullptr, Log *log = nullptr);
    ~StepForm();

    void setEnabled(bool state);

private slots:
    void on_leftFirstStepButton_clicked();

    void on_rightFirstStepButton_clicked();

    void on_feetTogetherButton_clicked();

private:
    Ui::StepForm *ui;
    SessionForm *session_;
    FrameWindow *frame_;

    Log* log_;
    int stepCount;

    void movement(const std::string code);
    void addLog(QString leg, bool correct, bool close, QTime time);
};

#endif // STEP_FORM_H
