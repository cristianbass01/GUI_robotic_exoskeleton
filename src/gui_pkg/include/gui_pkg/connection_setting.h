#ifndef CONNECTION_SETTING_H
#define CONNECTION_SETTING_H

#include <QWidget>

namespace Ui {
class connectionSetting;
}

class connectionSetting : public QWidget
{
    Q_OBJECT

public:
    explicit connectionSetting(QWidget *parent = nullptr);
    ~connectionSetting();

private:
    Ui::connectionSetting *ui;
};

#endif // CONNECTION_SETTING_H
