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
#include <user.h>

namespace Ui {
class SelectUserForm;
}

/**
 * @brief Widget che si occupa della selezione e creazione di un Utente
 */
class SelectUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit SelectUserForm(FrameWindow  *parent = nullptr, bool create = false, QString id = nullptr);
    ~SelectUserForm();

signals:
    //void on_BT_select_clicked();

private slots:
    /**
     * @brief Cambia lo stato tra modalità solo lettura e modalità di modifica, sono interessati gli elementi adibiti al inserimento dei dati
     * @param status True se si vole impostare in modalitè solo lettura, False per disattivarla
     */
    void setReadOnly(bool status);

    /**
     * @brief Esegue l'aggiunta del utente o la sua modifica a seconda se si è in Create o in Edit (Select)
     */
    void on_BT_create_clicked();

    /**
     * @brief Recupera l'utente e avvia il @link(TrainingForm)
     */
    void on_BT_selectUser_clicked();

    /**
     * @brief Visualizza LogView passando l'utente selezionato
     */
    void on_BT_viewLog_clicked();

    /**
     * @brief chiamata quando cambia l'elemento selezionato, si occupa di impostare i parametri
     * del utente selezionato al inteno dei vari cambi
     * @param index indice del elemento selezionato
     */
    void on_CB_selectUser_currentIndexChanged(int index);

    void on_BT_cancel_clicked();
    void on_BT_save_clicked();
    void on_finishButton_clicked();
    void on_BT_delete_clicked();

    /**
     * @brief Si occupa del popolamento della comboBox
     * @param start elemento da selezionare, ma se è presente un id valido allora viene selezionato quello
     * @param id imposta nella comboBox l'utente passato, se trovato
     */
    void createComboBox(int start, QString id);

    /**
     * @brief Cambia la grafica in base la modalità
     * @param edit true se sto modificando l'utente
     */
    void editMode(bool edit);

    /**
     * @brief Controlla che i dati inseriti rispettino dei canoni
     * @param edit true se sto modificando l'utente
     * @return
     */
    int checkCorrect(bool edit);

    /**
     * @brief Crea l'utente
     * @param overwrite obbliga la sovrascrizione
     */
    void createUser(bool overwrite);

public slots:
    void setEditMode();

private:
    Ui::SelectUserForm *ui;
    QString id_user;
    QList<QPair<QString, int>> users; // lista contenente (cognome + nome) del utente e la sua posizione nella ComboBox
    // ho fatto così per consentire di visualizzare solo nome e cognome senza l'id, poi recupero l'id tramite l'intero

    FrameWindow *frame_;
    int selectUser;

    /**
     * @brief Mostra un PopUp
     * @param text testo da mostrare
     * @param InformativeText informazioni aggiuntive
     * @return
     */
    bool popUpMsg(QString text, QString InformativeText);
};

#endif // SELECT_USER_FORM_H
