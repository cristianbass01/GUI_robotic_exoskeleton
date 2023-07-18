#ifndef FRAME_WINDOW_H
#define FRAME_WINDOW_H

#include <QMainWindow>
#include <QWidget>

namespace Ui {
class FrameWindow;
}

class FrameWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor -> setupUi and hide status bar
     * @param parent
     */
    explicit FrameWindow(QWidget *parent = nullptr);
    ~FrameWindow();

    /**
     * @brief customizeWindow inserting the widget in the parentLayout and
     *    erase the old one. save the objectName in currentForm
     * @param widget_to_insert
     */
    void customizeWindow(QWidget *widget_to_insert);

    /**
     * @brief setConnected -> set the children Form training or session as connected or not connected
     * @param state of the connection -> if true set connected, if false set not connected
     */
    void setConnected(bool state);

    /**
     * @brief setEnabled set toolBar and menu bar enable or disable
     * @param state -> if true set enable, disable otherwise
     */
    void setEnabled(bool state);

    /**
     * @brief showStatus show status bar with a message
     * @param msg message to be shown on statur bar
     */
    void showStatus(std::string msg);

    /**
     * @brief clearStatus clean message and hide status bar
     * @return current message of status bar
     */
    std::string clearStatus();

private slots:
    /**
     * @brief on_actionHome_triggered return to MainForm
     */
    void on_actionHome_triggered();

    /**
     * @brief on_actionClose_triggered close window
     */
    void on_actionClose_triggered();

    /**
     * @brief on_actionDemo_triggered set user to demo
     */
    void on_actionDemo_triggered();

    /**
     * @brief on_actionNew_User_triggered open select user form to create a user
     */
    void on_actionNew_User_triggered();

    /**
     * @brief on_actionView_User_triggered open select user form to view user info
     */
    void on_actionView_User_triggered();

    /**
     * @brief on_actionEdit_User_triggered open select user form to edit user
     */
    void on_actionEdit_User_triggered();

    /**
     * @brief on_actionTraining_Log_triggered open log window
     */
    void on_actionTraining_Log_triggered();

    /**
     * @brief on_actionMaximize_Window_triggered set window at maximum size
     */
    void on_actionMaximize_Window_triggered();

    /**
     * @brief on_actionChange_settings_triggered open connection setting form in change mode
     */
    void on_actionChange_settings_triggered();

    /**
     * @brief on_actionView_triggered open connection setting form in read only mode
     */
    void on_actionView_triggered();

    /**
     * @brief on_actionInfo_triggered open information message
     */
    void on_actionInfo_triggered();

    /**
     * @brief on_actionHelp_triggered open help message
     */
    void on_actionHelp_triggered();

    /**
     * @brief on_actionTraining_triggered open training Form
     */
    void on_actionTraining_triggered();

    /**
     * @brief closeEvent ask to confirmation to close window and shutdown connection
     * @param event
     */
    void closeEvent(QCloseEvent *event);

    /**
     * @brief on_actionMinimize_Window_triggered minimize window
     */
    void on_actionMinimize_Window_triggered();

private:
    Ui::FrameWindow *ui;

    //current Form in Layout Form
    QString currentForm;
};

#endif // FRAME_WINDOW_H
