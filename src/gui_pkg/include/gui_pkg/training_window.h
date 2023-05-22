#ifndef TRAINING_WINDOW_H
#define TRAINING_WINDOW_H

#include <QMainWindow>


namespace Ui {
class TrainingWindow;
}

class TrainingWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit TrainingWindow(QWidget *parent = nullptr);
  ~TrainingWindow();

private slots:
    void on_standButton_clicked();

    void on_stepButton_clicked();

    void on_walkButton_clicked();

    void on_controlButton_clicked();

    void on_finishButton_clicked();

private:
  Ui::TrainingWindow *ui;

};

#endif // TRAINING_WINDOW_H
