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
    explicit FrameWindow(QWidget *parent = nullptr);
    ~FrameWindow();

    void customizeWindow(QWidget *widget_to_insert);

    void setConnected(bool state);

private slots:
    void on_actionHome_triggered();
    void on_actionClose_triggered();

    void on_actionDemo_triggered();

    void on_actionNew_User_triggered();

    void on_actionView_User_triggered();

    void on_actionEdit_User_triggered();

    void on_actionTraining_Log_triggered();

    void on_actionMaximize_Window_triggered();

    void on_actionChange_settings_triggered();

    void on_actionView_triggered();

    void on_actionInfo_triggered();

    void on_actionHelp_triggered();

    void on_actionTraining_triggered();

private:
    Ui::FrameWindow *ui;
    QString currentForm;
};

#endif // FRAME_WINDOW_H
