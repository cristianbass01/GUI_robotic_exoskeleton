#include <user.h>

User::User() :
    dir_{""}, id_{""}, name_{""}, surname_{""}, birthday_{QDate(2000, 1, 1)}, sex_{""}, height_{170}, weight_{70}, upperLeg_{50}, lowerLeg_{50}
{}

User::User(QString dir, QString id, QString name, QString surname, QDate birthday, QString sex, int height, double weight, int upperLeg, int lowerLeg) :
    dir_{dir}, id_{id}, name_{name}, surname_{surname}, birthday_{birthday}, sex_{sex}, height_{height}, weight_{weight}, upperLeg_{upperLeg}, lowerLeg_{lowerLeg}
{}

//Getter
QString User::getId() const { return id_; }
QString User::getDir() const { return dir_; }
QString User::getName() const { return name_; }
QString User::getSurname() const { return surname_; }
QDate User::getBirthday() const { return birthday_; }
QString User::getSex() const { return sex_; }
int User::getHeight() const { return height_; }
double User::getWeight() const { return weight_; }
int User::getUpperLeg() const { return upperLeg_; }
int User::getLowerLeg() const { return lowerLeg_; }

//Setter
void User::setId(QString id) { id_ = id; }
void User::setDir(QString dir) { dir_ = dir; }
void User::setName(QString name) { name_ = name; }
void User::setSurname(QString surname) { surname_ = surname; }
void User::setBirthday(QDate birthday) { birthday_ = birthday; }
void User::setSex(QString sex) { sex_ = sex; }
void User::setHeight(int height) { height_ = height; }
void User::setWeight(double weight) { weight_ = weight; }
void User::setUpperLeg(int upperLeg) { upperLeg_ = upperLeg; }
void User::setLowerLeg(int lowerLeg) { lowerLeg_ = lowerLeg; }

