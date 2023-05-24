#ifndef FRAME_WINDOW_H
#define FRAME_WINDOW_H

#include <QMainWindow>

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

private slots:
    void on_actionHome_triggered();

private:
    Ui::FrameWindow *ui;
};

#endif // FRAME_WINDOW_H
