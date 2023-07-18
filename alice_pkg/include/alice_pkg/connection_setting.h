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
    /**
     * @brief Constructor ConnectionSetting
     * @param parent
     * @param read only if onlyView is true, writtable if not
     */
    explicit ConnectionSetting(QWidget *parent = nullptr, bool onlyView = true);
    ~ConnectionSetting();

private:
    /**
     * @brief Setup the central widget with the parameters
     * @param read only if changeable is false, writtable if true
     */
    void setup(bool changeable);

private slots:
    /**
     * @brief Clore the application
     */
    void on_closeButton_clicked();

    /**
     * @brief Setup window as changeable
     */
    void on_changeButton_clicked();

    /**
     * @brief Discard changes and close window
     */
    void on_discardButton_clicked();

    /**
     * @brief Send to ros master the new parameters and close window
     */
    void on_saveButton_clicked();

private:
    Ui::ConnectionSetting *ui;
};

#endif // CONNECTION_SETTING_H
