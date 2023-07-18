#ifndef WALKING_WINDOW_H
#define WALKING_WINDOW_H

#include <QWidget>
#include "connected_component.h"
#include "frame_window.h"
#include "user.h"
#include <log.h>

namespace Ui {
class SessionForm;
}

class SessionForm : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief SessionForm constructor that hide loading icon and
     *    if timer is active try to connect to the device and restart timer
     * @param parent of type frameWindow
     */
    explicit SessionForm(FrameWindow * parent = nullptr);
    ~SessionForm();

    /**
     * @brief customizeForm in parent Layout with stepform, walkingform or controlform
     * @param widget_to_insert
     */
    void customizeForm(QWidget *widget_to_insert);

    /**
     * @brief getFrame
     * @return the reference to parent frame
     */
    FrameWindow *getFrame(){return this->frame_;}

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
    void movement(const std::string code);

    /**
     * @brief setEnabled change button availability
     * @param state = if true set enable, disable otherwise
     */
    void setEnabled(bool state);

    /**
     * @brief updateImage set image of the type of the step in current state
     */
    void updateImage();


public slots:

    /**
     * @brief on_connectButton_clicked show loading icon and try connection
     */
    void on_connectButton_clicked();

private slots:
    /**
     * @brief on_controlButton_clicked open control walking window
     */
    void on_controlButton_clicked();

    /**
     * @brief on_stepButton_clicked open step window
     */
    void on_stepButton_clicked();

    /**
     * @brief on_returnButton_clicked return to training form
     */
    void on_returnButton_clicked();

    /**
     * @brief on_walkButton_clicked open walking window
     */
    void on_walkButton_clicked();

    /**
     * @brief on_sitButton_clicked call movement(sit)
     */
    void on_sitButton_clicked();

    /**
     * @brief on_storageButton_clicked call movement(storage)
     */
    void on_storageButton_clicked();

    /**
     * @brief on_standButton_clicked call movement(stand)
     */
    void on_standButton_clicked();

    /**
     * @brief tryConnection try to connect to the device and start the timer
     *   if not connected stop the timer
     */
    void tryConnection();

    /**
     * @brief updateStatus sees currentstate of connectedComponent and show lbstatus
     *    to make step disable if current status is not the right status to start the movement (usually stand)
     */
    void updateStatus();

    /**
     * @brief on_shutdownButton_clicked close connection to the device
     */
    void on_shutdownButton_clicked();

    /**
     * @brief Crea un file di log associato al utente
     * @return log associato al utente
     */
    Log* createLog();

private:
    Ui::SessionForm *ui;
    FrameWindow * frame_; // pointer to parent frame
    QSharedPointer<User> user_; // pointer to user

    QWidget *form_ = nullptr; // pointer to children form

    // path to image resources
    const QString LEFTSTEP = QString::fromStdString(":/Alice/Alice/Alice_left_step.png");
    const QString RIGHTSTEP = QString::fromStdString(":/Alice/Alice/Alice_right_step.png");
    const QString LEFTCLOSE = QString::fromStdString(":/Alice/Alice/Alice_step_five.png");
    const QString SIT = QString::fromStdString(":/Alice/Alice/Alice_sit_straight.png");
    const QString STORAGE = QString::fromStdString(":/Alice/Alice/Alice_sitting_exercises.png");
    const QString STAND = QString::fromStdString(":/Alice/Alice/Alice_stand_straight.png");
    const QString NOTCONNECTED = QString::fromStdString(":/Alice/Alice/Alice_not_connected.png");

    /**
     * @brief setImage change image of Alice to the one given
     */
    void setImage(const QString);
};

#endif // WALKING_WINDOW_H
