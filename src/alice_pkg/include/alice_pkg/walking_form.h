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
    /**
     * @brief WalkingForm constructor that save frame and session and make form enable
     * @param parent of type SessionForm
     * @param log to save movements
     */
    explicit WalkingForm(SessionForm *parent = nullptr, Log *log = nullptr);
    ~WalkingForm();

    /**
     * @brief setEnabled change availability of buttons
     * @param if state is false disable all buttons, otherwise set enable
     */
    void setEnabled(bool state);

private slots:
    /**
     * @brief on_startButton_clicked set start disable and stop enable
     *   -> if connected to the device, initialize thread with the number of steps and log and start it
     *      connect WalkThread::progressUpdated to ControlForm::updateProgressBar and WalkThread::stopped
     *      to ControlForm::finishProgressBar
     *   -> if not connected launch a message of error and make the window available again
     */
    void on_startButton_clicked();

    /**
     * @brief on_stopButton_clicked change stop button text in "stopping..." and stop thread
     */
    void on_stopButton_clicked();

    /**
     * @brief updateProgressBar update the progress bar with a new value and change the frame status bar
     *    with a new message
     * @param value = number of single step (2 single steps = 1 walk)
     */
    void updateProgressBar(int value);

    /**
     * @brief finishProgressBar hide progress bar, disable Stop and change its text in "Stop",
     *    enable Start and clear frame status bar
     */
    void finishProgressBar();

private:
    Ui::WalkingForm *ui;

    /**
     * @brief session_ reference to parent session
     */
    SessionForm *session_; // reference to parent session

    /**
     * @brief frame_ reference to session's parent frame
     */
    FrameWindow *frame_; // reference to parent frame

    Log* log_;

    /**
     * @brief thread_ to start walking
     */
    QSharedPointer<WalkThread> thread_; // pointer to thread


};

#endif // WALKING_FORM_H
