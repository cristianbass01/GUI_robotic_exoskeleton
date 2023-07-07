#ifndef TRAINING_WINDOW_H
#define TRAINING_WINDOW_H

#include <QWidget>
#include "frame_window.h"

#include <log.h>
#include "user.h"


namespace Ui {
class TrainingForm;
}

class TrainingForm : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingForm(FrameWindow *parent = nullptr);
    ~TrainingForm();

    FrameWindow* getFrame(){return this->frame_;}
    void setConnected(bool state);

    void displayUser();

    void movement(const std::string);

    void setEnabled(bool state);


private slots:
    void on_standButton_clicked();

    void on_stepButton_clicked();

    void on_walkButton_clicked();

    void on_controlButton_clicked();

    void on_finishButton_clicked();

    void on_connectButton_clicked();

    void tryConnection();

    void on_sitButton_clicked();

    void on_storageButton_clicked();

    /**
     * @brief Crea un file di log associato al utente
     * @return log associato al utente
     */
    Log* createLog();

    void on_shutdownButton_clicked();

private:
    Ui::TrainingForm *ui;
    FrameWindow *frame_;
};

#endif // TRAINING_WINDOW_H
