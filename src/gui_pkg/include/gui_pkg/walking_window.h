#ifndef WALKING_WINDOW_H
#define WALKING_WINDOW_H

#include <QMainWindow>
#include "connected_component.h"

namespace Ui {
class WalkingWindow;
}

class WalkingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WalkingWindow(QWidget *parent = nullptr);
    ~WalkingWindow();

private slots:
    void on_controlWindowButton_clicked();

    void on_stepWindowButton_clicked();

    void on_returnButton_clicked();

private:
    Ui::WalkingWindow *ui;
};

#endif // WALKING_WINDOW_H
