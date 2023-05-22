#ifndef STEP_WINDOW_H
#define STEP_WINDOW_H

#include <QMainWindow>
#include "connected_component.h"

namespace Ui {
class StepWindow;
}

class StepWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StepWindow(QWidget *parent = nullptr);
    ~StepWindow();

private slots:
    void on_controlWindowButton_clicked();

    void on_returnButton_clicked();

    void on_walkingWindowButton_clicked();

    void on_leftFirstStepButton_clicked();

private:
    Ui::StepWindow *ui;
};

#endif // STEP_WINDOW_H
