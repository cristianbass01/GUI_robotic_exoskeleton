#ifndef SELECT_USER_FORM_H
#define SELECT_USER_FORM_H

#include <QWidget>
#include <QObject>
#include <QTextStream>
#include <QString>
#include <iostream>
#include <fstream>
#include <QList>
#include <ros/ros.h>
#include <frame_window.h>

namespace Ui {
class SelectUserForm;
}

class SelectUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit SelectUserForm(FrameWindow  *parent = nullptr, bool create = false);
    ~SelectUserForm();

signals:
    //void on_BT_select_clicked();

private slots:
    void setReadOnly(bool status, bool id);
    void on_BT_create_clicked();
    void on_BT_selectUser_clicked();
    void createComboBox(int start, QString id);
    void on_CB_selectUser_currentIndexChanged(int index);

    void on_BT_viewLog_clicked();
    void createUser(bool overwrite);

private:
    Ui::SelectUserForm *ui;
    QString id_user;
    QList<QPair<QString, int>> users;
    std::shared_ptr<FrameWindow> frame_;
    int currentUser;
    bool overWriteMsg(QString text, QString InformativeText);
};

#endif // SELECT_USER_FORM_H
