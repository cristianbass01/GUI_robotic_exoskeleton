#include <QString>
#include <QDate>

#ifndef USER_H
#define USER_H

class User {
private:
    QString dir_;
    QString id_;
    QString name_;
    QString surname_;
    QDate birthday_;
    QString sex_;
    int height_;
    double weight_;
    int femur_;
    int tibia_;

public:
    User();
    User(QString dir, QString id, QString name, QString surname, QDate birthday, QString sex, int height, double weight, int femur, int tibia);

    // Getters
    QString getDir() const;
    QString getId() const;
    QString getName() const;
    QString getSurname() const;
    QDate getBirthday() const;
    QString getSex() const;
    int getHeight() const;
    double getWeight() const;
    int getFemur() const;
    int getTibia() const;

    // Setters
    void setDir(QString dir);
    void setId(QString id);
    void setName(QString name);
    void setSurname(QString surname);
    void setBirthday(QDate birthday);
    void setSex(QString sex);
    void setHeight(int height);
    void setWeight(double weight);
    void setFemur(int femur);
    void setTibia(int tibia);
};

#endif // USER_H
