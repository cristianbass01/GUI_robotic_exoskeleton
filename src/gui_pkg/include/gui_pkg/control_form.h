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

public:
    explicit ControlForm(SessionForm *parent = nullptr, Log *log = nullptr);
    ~ControlForm();

    void setEnabled(bool state);

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void updateProgressBar(int value);

    void finishProgressBar();

private:
    Ui::ControlForm *ui;
    SessionForm *session_;
    FrameWindow *frame_;

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
