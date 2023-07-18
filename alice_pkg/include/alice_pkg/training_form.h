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
    /**
     * @brief TrainingForm constructor that hide loading icon and
     *    if timer is active try to connect to the device and restart timer
     * @param parent of type frameWindow
     */
    explicit TrainingForm(FrameWindow *parent = nullptr);
    ~TrainingForm();

    /**
     * @brief getFrame
     * @return the reference to parent frame
     */
    FrameWindow* getFrame(){return this->frame_;}

    /**
     * @brief setConnected change buttons of connection
     * @param if state is true than connected, so it change the red button from not connected to connected in green,
     *    and show shutdown button, if false do the opposite
     */
    void setConnected(bool state);

    /**
     * @brief displayUser change the name of the box user
     */
    void displayUser();

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
    void movement(const std::string);

    /**
     * @brief setEnabled change button availability
     * @param state = if true set enable, disable otherwise
     */
    void setEnabled(bool state);


private slots:
    /**
     * @brief on_standButton_clicked call movement(stand)
     */
    void on_standButton_clicked();

    /**
     * @brief on_stepButton_clicked open step window
     */
    void on_stepButton_clicked();

    /**
     * @brief on_walkButton_clicked open walking window
     */
    void on_walkButton_clicked();

    /**
     * @brief on_controlButton_clicked open control walking window
     */
    void on_controlButton_clicked();

    /**
     * @brief on_finishButton_clicked close application
     */
    void on_finishButton_clicked();

    /**
     * @brief on_connectButton_clicked show loading icon and try connection
     */
    void on_connectButton_clicked();

    /**
     * @brief tryConnection try to connect to the device and start the timer
     *   if not connected stop the timer
     */
    void tryConnection();

    /**
     * @brief on_sitButton_clicked call movement(sit)
     */
    void on_sitButton_clicked();

    /**
     * @brief on_storageButton_clicked call movement(storage)
     */
    void on_storageButton_clicked();

    /**
     * @brief Crea un file di log associato al utente
     * @return log associato al utente
     */
    Log* createLog();

    /**
     * @brief on_shutdownButton_clicked close connection to the device
     */
    void on_shutdownButton_clicked();

private:
    Ui::TrainingForm *ui;
    FrameWindow *frame_; // pointer to parent frame
};

#endif // TRAINING_WINDOW_H
