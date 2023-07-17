#ifndef CONTROL_FORM_H
#define CONTROL_FORM_H

#include <QWidget>

#include "session_form.h"
#include "frame_window.h"
#include <log.h>
#include <QTime>
#include "walk_thread.h"

namespace Ui {
class ControlForm;
}

class ControlForm : public QWidget
{
    Q_OBJECT

public:/**
     * @brief Constructor of the control walking Form, set stop unavailable and hide progressBar
     * @param parent = the session Form of training
     * @param log = log to save progresses
     */
    explicit ControlForm(SessionForm *parent = nullptr, Log *log = nullptr);
    ~ControlForm();

    /**
     * @brief Disable or enable start button
     * @param state = true if enable or false otherwise
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
    Ui::ControlForm *ui;

    /**
     * @brief session_ reference to parent session
     */
    SessionForm *session_;

    /**
     * @brief frame_ reference to session's parent frame
     */
    FrameWindow *frame_;

    /**
     * @brief thread_ to start walking
     */
    QSharedPointer<WalkThread> thread_;

    Log* log_;

    /**
     * @brief Aggiunge Log per l'azione Control
     * @param leg Gamba con cui è stata eseguito il movimento
     * @param correct Se il passo si è concluso correttamente
     * @param time Tempo di esecuzione
     */
    void addLog(QString leg, bool correct, QTime time);
};

#endif // CONTROL_FORM_H
