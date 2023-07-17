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
    /**
     * @brief StepForm constructor that save frame and session and make form enable
     * @param parent of type SessionForm
     * @param log to save movements
     */
    explicit StepForm(SessionForm *parent = nullptr, Log *log = nullptr);
    ~StepForm();

    /**
     * @brief setEnabled change availability of buttons
     * @param if state is false disable all buttons, otherwise set enable just some button depending on last step
     */
    void setEnabled(bool state);

private slots:
    /**
     * @brief on_leftFirstStepButton_clicked call movement(left step)
     */
    void on_leftFirstStepButton_clicked();

    /**
     * @brief on_rightFirstStepButton_clicked call movement(right step)
     */
    void on_rightFirstStepButton_clicked();

    /**
     * @brief on_feetTogetherButton_clicked call movement(left close)
     */
    void on_feetTogetherButton_clicked();

private:
    Ui::StepForm *ui;
    SessionForm *session_; // parent session
    FrameWindow *frame_; // parent frame of session

    Log* log_;
    int stepCount;

    /**
     * @brief movement
     *    -> set children form and session form to disable
     *    -> if not connected, try to connect
     *    -> if connected, send the code to connectedComponent to perform the step
     *    -> if the step is not performed launch a message box
     *    -> update image
     *    -> set children form and session form to enable
     * @param code of the step to perform
     */
    void movement(const std::string code);

    /**
     * @brief Aggiunge Log per l'azione Step
     * @param leg Gamba con cui è stata eseguito il movimento
     * @param correct Se il passo si è concluso correttamente
     * @param close Se il passo è di chiusura
     * @param time Tempo di esecuzione
     */
    void addLog(QString leg, bool correct, bool close, QTime time);
};

#endif // STEP_FORM_H
