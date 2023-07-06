#ifndef CONNECTION_SETTING_H
#define CONNECTION_SETTING_H

#include <QDialog>

namespace Ui {
class ConnectionSetting;
}

class ConnectionSetting : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionSetting(QWidget *parent = nullptr, bool onlyView = true);
    ~ConnectionSetting();

private:
    void setup(bool changeable);

private slots:
    void on_closeButton_clicked();

    void on_changeButton_clicked();

    void on_discardButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::ConnectionSetting *ui;
};

#endif // CONNECTION_SETTING_H
