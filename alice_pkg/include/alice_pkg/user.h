#include <QString>
#include <QDate>

#ifndef USER_H
#define USER_H

/**
 * @brief La classe User rappresenta un utente con le sue informazioni personali.
 */
class User {
private:
    QString dir_;        // Directory dell'utente
    QString id_;         // ID dell'utente
    QString name_;       // Nome dell'utente
    QString surname_;    // Cognome dell'utente
    QDate birthday_;     // Data di nascita dell'utente
    QString sex_;        // Sesso dell'utente
    int height_;         // Altezza dell'utente
    double weight_;      // Peso dell'utente
    int upperLeg_;       // Lunghezza gamba superiore dell'utente
    int lowerLeg_;       // Lunghezza gamba inferiore dell'utente

public:
    /**
     * @brief Costruttore predefinito.
     * Inizializza un oggetto User con valori predefiniti per tutti gli attributi.
     */
    User() :
      dir_{""}, id_{""}, name_{""}, surname_{""}, birthday_{QDate(2000, 1, 1)}, sex_{""}, height_{170}, weight_{70}, upperLeg_{50}, lowerLeg_{50}
  {}

    /**
     * @brief Costruttore con parametri.
     * Crea un oggetto User con i valori specificati per gli attributi.
     * @param dir La directory dell'utente.
     * @param id L'ID dell'utente.
     * @param name Il nome dell'utente.
     * @param surname Il cognome dell'utente.
     * @param birthday La data di nascita dell'utente.
     * @param sex Il sesso dell'utente.
     * @param height L'altezza dell'utente.
     * @param weight Il peso dell'utente.
     * @param upperLeg La lunghezza della gamba superiore dell'utente.
     * @param lowerLeg La lunghezza della gamba inferiore dell'utente.
     */
    User(QString dir, QString id, QString name, QString surname, QDate birthday, QString sex, int height, double weight, int upperLeg, int lowerLeg) :
      dir_{dir}, id_{id}, name_{name}, surname_{surname}, birthday_{birthday}, sex_{sex}, height_{height}, weight_{weight}, upperLeg_{upperLeg}, lowerLeg_{lowerLeg}
  {}

    // Getters   
    /**
     * @brief Restituisce l'ID dell'utente.
     * @return L'ID dell'utente.
     */
    QString getId() const { return id_; }

    /**
     * @brief Restituisce la directory dell'utente.
     * @return La directory dell'utente.
     */
    QString getDir() const { return dir_; }

    /**
     * @brief Restituisce il nome dell'utente.
     * @return Il nome dell'utente.
     */
    QString getName() const { return name_; }

    /**
     * @brief Restituisce il cognome dell'utente.
     * @return Il cognome dell'utente.
     */
    QString getSurname() const { return surname_; }

    /**
     * @brief Restituisce la data di nascita dell'utente.
     * @return La data di nascita dell'utente.
     */
    QDate getBirthday() const { return birthday_; }

    /**
     * @brief Restituisce il sesso dell'utente.
     * @return Il sesso dell'utente.
     */
    QString getSex() const { return sex_; }

    /**
     * @brief Restituisce l'altezza dell'utente.
     * @return L'altezza dell'utente.
     */
    int getHeight() const { return height_; }

    /**
     * @brief Restituisce il peso dell'utente.
     * @return Il peso dell'utente.
     */
    double getWeight() const { return weight_; }

    /**
     * @brief Restituisce la lunghezza della gamba superiore dell'utente.
     * @return La lunghezza della gamba superiore dell'utente.
     */
    int getUpperLeg() const { return upperLeg_; }

    /**
     * @brief Restituisce la lunghezza della gamba inferiore dell'utente.
     * @return La lunghezza della gamba inferiore dell'utente.
     */
    int getLowerLeg() const { return lowerLeg_; }

    // Setters
    /**
     * @brief Imposta l'ID dell'utente.
     * @param id L'ID da assegnare all'utente.
     */
    void setId(QString id) { id_ = id; }

    /**
     * @brief Imposta la directory dell'utente.
     * @param dir La directory da assegnare all'utente.
     */
    void setDir(QString dir) { dir_ = dir; }

    /**
     * @brief Imposta il nome dell'utente.
     * @param name Il nome da assegnare all'utente.
     */
    void setName(QString name) { name_ = name; }

    /**
     * @brief Imposta il cognome dell'utente.
     * @param surname Il cognome da assegnare all'utente.
     */
    void setSurname(QString surname) { surname_ = surname; }

    /**
     * @brief Imposta la data di nascita dell'utente.
     * @param birthday La data di nascita da assegnare all'utente.
     */
    void setBirthday(QDate birthday) { birthday_ = birthday; }

    /**
     * @brief Imposta il sesso dell'utente.
     * @param sex Il sesso da assegnare all'utente.
     */
    void setSex(QString sex) { sex_ = sex; }

    /**
     * @brief Imposta l'altezza dell'utente.
     * @param height L'altezza da assegnare all'utente.
     */
    void setHeight(int height) { height_ = height; }

    /**
     * @brief Imposta il peso dell'utente.
     * @param weight Il peso da assegnare all'utente.
     */
    void setWeight(double weight) { weight_ = weight; }

    /**
     * @brief Imposta la lunghezza della gamba superiore dell'utente.
     * @param upperLeg La lunghezza della gamba superiore da assegnare all'utente.
     */
    void setUpperLeg(int upperLeg) { upperLeg_ = upperLeg; }

    /**
     * @brief Imposta la lunghezza della gamba inferiore dell'utente.
     * @param lowerLeg La lunghezza della gamba inferiore da assegnare all'utente.
     */
    void setLowerLeg(int lowerLeg) { lowerLeg_ = lowerLeg; }
};

#endif // USER_H
