#ifndef CONTROL_WINDOW_H
#define CONTROL_WINDOW_H

#include <QMainWindow>
#include "connected_component.h"

namespace Ui {
class ControlWindow;
}

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = nullptr);
    ~ControlWindow();

private slots:
    void on_walkingWindowButton_clicked();

    void on_stepWindowButton_clicked();

    void on_returnButton_clicked();

private:
    Ui::ControlWindow *ui;
};

#endif // CONTROL_WINDOW_H
